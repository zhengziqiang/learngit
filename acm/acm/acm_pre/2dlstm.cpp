/*==============================================================================
    > File Name: 2dlstm.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2016年09月12日 星期一 15时09分41秒
 ==========================================================================*/
#include <algorithm>
#include <cmath>
#include <vector>
#include "caffe/filler.hpp"
#include "caffe/layer.hpp"
#include "caffe/layers/lstm_layer.hpp"

namespace caffe {

template <typename Dtype>
inline Dtype sigmoid(Dtype x) {
  return 1. / (1. + exp(-x));
}

//template <typename Dtype>
//inline Dtype tanh(Dtype x) {
//  return 2. * sigmoid(2. * x) - 1.;
//}
template <typename Dtype>
inline Dtype dtanh(Dtype y) {
	return 1.-y*y;
}
template <typename Dtype>
inline Dtype dsigmoid(Dtype y) {
	return y*(1-y);
}
template <typename Dtype>
void LSTMUnitLayer<Dtype>::LayerSetUp(const vector<Blob<Dtype>*>& bottom,
	const vector<Blob<Dtype>*>& top)
{
	LSTMUnitParameter lstm_param = this->layer_param_.lstm_param();
	if(!(lstm_param.has_kernel_size() ||
		lstm_param.has_kernel_h() || lstm_param.has_kernel_w()))
		cout << "No kernel size detected!Set kernel size as default value (1)!"<<endl;
	if (!(lstm_param.has_stride() ||
		lstm_param.has_stride_h() || lstm_param.has_stride_w()))
		cout << "No stride size detected!Set stride size as default value (1)!"<<endl;
	if (lstm_param.has_kernel_size()) {
		kernel_height_ = kernel_width_ = lstm_param.kernel_size();
	}
	else if (lstm_param.has_kernel_h() && lstm_param.has_kernel_w()){
		kernel_height_ = lstm_param.kernel_h();
		kernel_width_ = lstm_param.kernel_w();
	}
	else
	{
		kernel_height_ = 1;
		kernel_width_ = 1;
	}
	if (lstm_param.has_stride()) {
		stride_height_ = stride_width_ = lstm_param.stride();
	}
	else if (lstm_param.has_stride_h() && lstm_param.has_stride_w()){
		stride_height_ = lstm_param.stride_h();
		stride_width_ = lstm_param.stride_w();
	}
	else
	{
		stride_height_ = 1;
		stride_width_ = 1;
	}
	input_height_ = bottom[0]->height();
	input_width_ = bottom[0]->width();
	output_height_ = (input_height_ -  kernel_height_)/stride_height_ + 1;
	output_width_ = (input_width_ - kernel_width_)/stride_width_ + 1;
	hidden_dim_ = lstm_param.num_output();
	channels_ = bottom[0]->shape(1);
	CHECK_GT(input_height_, 0);
	CHECK_GT(input_width_, 0);
	CHECK_GT(kernel_height_, 0);
	CHECK_GT(kernel_width_, 0);
	CHECK_GT(output_height_, 0);
	CHECK_GT(output_width_, 0);
	const int num_instances = bottom[0]->shape(0);	//n
	const int num_output = this->layer_param_.lstm_param().num_output();
	for (int i = 0; i < bottom.size(); ++i) {
		CHECK_EQ(4, bottom[0]->num_axes());	//input shape should be n*c*h*w
	}

	int tempint = bottom[0]->shape(0);
	tempint = bottom[0]->shape(1);
	tempint = bottom[0]->shape(2);
	tempint = bottom[0]->shape(3);
	this->blobs_.resize(4);//input-h, hx-h,hy-h,cell-gate
	weight_groups = 4;//4 groups:  0 for net input, 1 for input gate, 2 for output gate, 3 for forget gate 
	vector<int> weight_shape(4);
	weight_shape[0] = hidden_dim_;	//hidden neuron number
	weight_shape[1] = bottom[0]->shape(1);	//bottom channels
	weight_shape[2] = kernel_height_*kernel_width_;	//input window size
	weight_shape[3] = weight_groups;

	
	
	this->blobs_[0].reset(new Blob<Dtype>(weight_shape));

	vector<int> weight_shape_hh(3);	//input-h, hx-h,hy-h
	weight_shape_hh[0] = weight_groups;	//4 groups: 0 for net input, 1 for input gate, 2 for output gate, 3 for forget gate 
	weight_shape_hh[1] = hidden_dim_;	//hidden to hidden
	weight_shape_hh[2] = hidden_dim_;	//hidden neuron number
	for (int i = 1; i < 3; i++)
		this->blobs_[i].reset(new Blob<Dtype>(weight_shape_hh));
	
	vector<int> weight_shape_cg(2);	//cell-gate
	weight_shape_cg[0] = hidden_dim_;	//cell to hidden
	weight_shape_cg[1] = 5;	//5 groups: 0 for input gate x, 1 for input gate y, 2 for forget gate x 3 for forget gate y 4 for output gate, 
	this->blobs_[3].reset(new Blob<Dtype>(weight_shape_cg));
	shared_ptr<Filler<Dtype> > weight_filler(GetFiller<Dtype>(
		this->layer_param_.lstm_param().weight_filler()));
	for (int i = 0; i < 4; i++)
	{
		weight_filler->Fill(this->blobs_[i].get());
	}
	int topcount = output_height_*output_width_*hidden_dim_;
	vector<int> map_shape;
	map_shape.push_back(bottom[0]->num());
	map_shape.push_back(output_height_);
	map_shape.push_back(output_width_);
	map_shape.push_back(hidden_dim_);
	cell_states_map_.Reshape(map_shape);
	input_gates_map_.Reshape(map_shape);
	output_gates_map_.Reshape(map_shape);
	forget_gates_map_.Reshape(map_shape);
	net_inputs_map_.Reshape(map_shape);
	cell_outputs_diff_.Reshape(map_shape);
	cell_states_diff_.Reshape(map_shape);
	input_gates_diff_.Reshape(map_shape);
	output_gates_diff_.Reshape(map_shape);
	forget_gates_diff_.Reshape(map_shape);
	//caffe_set(topcount, Dtype(0), cell_states_map);
	direction = lstm_param.direction();
	//caffe_set(bottom[0]->count(), Dtype(0), this->blobs_);	//When should reset diff?
}

template <typename Dtype>
void LSTMUnitLayer<Dtype>::Reshape(const vector<Blob<Dtype>*>& bottom,
  const vector<Blob<Dtype>*>& top) {
  input_height_ = bottom[0]->height();
  input_width_ = bottom[0]->width();
  output_height_ = (input_height_ - kernel_height_) / stride_height_ + 1;
  output_width_ = (input_width_ - kernel_width_) / stride_width_ + 1;
  hidden_dim_ = this->layer_param_.lstm_param().num_output();
  top[0]->Reshape(bottom[0]->num(), hidden_dim_, output_height_, output_width_);
}

template <typename Dtype>
void LSTMUnitLayer<Dtype>::Forward_cpu(const vector<Blob<Dtype>*>& bottom,
    const vector<Blob<Dtype>*>& top) {
  const Dtype* bottom_data = bottom[0]->cpu_data();
  Dtype* top_data = top[0]->mutable_cpu_data();
  const int top_count = top[0]->count();
  caffe_set(top_count, Dtype(0), top_data);
  const Dtype* weight_ih = this->blobs_[0]->cpu_data();
  const Dtype* weight_hhx = this->blobs_[1]->cpu_data();
  const Dtype* weight_hhy = this->blobs_[2]->cpu_data();
  const Dtype* weight_cg = this->blobs_[3]->cpu_data();
  Dtype net_input = 0;
  Dtype input_gate = 0;
  Dtype output_gate = 0;
  Dtype forget_gate = 0;
  Dtype cell_states = 0;
  Dtype cell_output = 0;
  Dtype hidden_x_input = 0;
  Dtype hidden_y_input = 0;
  Dtype cell_states_x_1 = 0;
  Dtype cell_states_y_1 = 0;
  Dtype cell_outputs_x_1 = 0;
  Dtype cell_outputs_y_1 = 0;
  int topcount = output_width_*output_height_*hidden_dim_*bottom[0]->num();
  Dtype* cell_states_map=cell_states_map_.mutable_cpu_data();
  Dtype* input_gates_map = input_gates_map_.mutable_cpu_data();
  Dtype* output_gates_map = output_gates_map_.mutable_cpu_data();
  Dtype* forget_gates_map = forget_gates_map_.mutable_cpu_data();
  Dtype* net_inputs_map=net_inputs_map_.mutable_cpu_data();
  caffe_set(topcount, Dtype(0), cell_states_map);
  caffe_set(topcount, Dtype(0), input_gates_map);
  caffe_set(topcount, Dtype(0), output_gates_map);
  caffe_set(topcount, Dtype(0), forget_gates_map);
  caffe_set(topcount, Dtype(0), net_inputs_map);
  for (int n = 0; n < bottom[0]->num(); ++n) {	  
	  if (direction == 1)	//top left
	  {
		  for (int oh = 0; oh < output_height_; ++oh) {
			  for (int ow = 0; ow < output_width_; ++ow) {
				 
				  int sub_weight_offset_h = hidden_dim_*hidden_dim_;
					  for (int hi = 0; hi < hidden_dim_; hi++)	//hid=num_output
					  {
						  net_input = 0;
						  input_gate = 0;
						  output_gate = 0;
						  forget_gate = 0;
						  cell_states = 0;
						  cell_output = 0;
						  int weight_offset = channels_*kernel_height_*kernel_width_*hi*weight_groups;
						  for (int c = 0; c < channels_; ++c) {
							 
							  int sub_weight_offset = kernel_height_*kernel_width_;
							  int input_offset = c*input_width_*input_height_;
							  

							  int hstart = oh * stride_height_;
							  int wstart = ow * stride_width_;
							  int hend = min(hstart + kernel_height_, input_height_);
							  int wend = min(wstart + kernel_width_, input_width_);
							  hstart = max(hstart, 0);
							  wstart = max(wstart, 0);
							  int weight_index = 0;
							  for (int h = hstart; h < hend; ++h) {
								  int index = h * input_width_;
								  for (int w = wstart; w < wend; ++w) {
									  index += w;

									  net_input += weight_ih[weight_index + weight_offset] * bottom_data[index + input_offset];
									  input_gate += weight_ih[weight_index + weight_offset + sub_weight_offset] * bottom_data[index + input_offset];
									  output_gate += weight_ih[weight_index + weight_offset + sub_weight_offset * 2] * bottom_data[index + input_offset];
									  forget_gate += weight_ih[weight_index + weight_offset + sub_weight_offset * 3] * bottom_data[index + input_offset];
									  weight_index++;
								  }
							  }
							  weight_offset += c*kernel_height_*kernel_width_*weight_groups;
						  }
						  const int output_index = oh * output_width_ + ow + hi*output_height_*output_width_;
						  for (int hj = 0; hj<hidden_dim_; hj++)
						  {
							  if (ow>0)
								  cell_states_x_1 = cell_states_map[output_index - 1];
							  else
								  cell_states_x_1 = 0;
							  if (oh>0)
								  cell_states_y_1 = cell_states_map[output_index - output_width_];
							  else
								  cell_states_y_1 = 0;
							  if (ow>0)
								  cell_outputs_x_1 = top_data[output_index - 1];
							  else
								  cell_outputs_x_1 = 0;
							  if (oh>0)
								  cell_outputs_y_1 = top_data[output_index - output_width_];
							  else
								  cell_outputs_y_1 = 0;
							  const int weight_h_index = hi*hidden_dim_ + hj;
							  
							  net_input += weight_hhx[weight_h_index] * cell_outputs_x_1;
							  net_input += weight_hhy[weight_h_index] * cell_outputs_y_1;

							  input_gate += weight_hhx[weight_h_index + sub_weight_offset_h] * cell_outputs_x_1;
							  input_gate += weight_hhy[weight_h_index + sub_weight_offset_h] * cell_outputs_y_1;
							  
							  output_gate += weight_hhx[weight_h_index + sub_weight_offset_h * 2] * cell_outputs_x_1;
							  output_gate += weight_hhy[weight_h_index + sub_weight_offset_h * 2] * cell_outputs_y_1;
							  
							  forget_gate += weight_hhx[weight_h_index + sub_weight_offset_h * 3] * cell_outputs_x_1;
							  forget_gate += weight_hhx[weight_h_index + sub_weight_offset_h * 3] * cell_outputs_y_1;
							  
						  }
						  const int weight_c_index = hi * 5;
						  input_gate += weight_cg[weight_c_index] * cell_states_x_1;
						  input_gate += weight_cg[weight_c_index + 1] * cell_states_y_1;	//8.5
						 
						  input_gate = sigmoid(input_gate);	//8.6
						  input_gates_map[output_index] = input_gate;

						  forget_gate += weight_cg[weight_c_index + 2] * cell_states_x_1;
						  forget_gate += weight_cg[weight_c_index + 3] * cell_states_y_1;	//8.7
						  forget_gate = sigmoid(forget_gate);	//8.8
						  forget_gates_map[output_index] = forget_gate;
						 
						  net_input = tanh(net_input);	//8.9
						  net_inputs_map[output_index] = net_input;
						  cell_states_map[output_index] += input_gate*net_input + forget_gate*cell_states_x_1 + forget_gate*cell_states_y_1;	//8.10
						  if (cell_states_map[output_index] > 5)
							  cell_states_map[output_index] = 5;
						  else if (cell_states_map[output_index] < -5)
							  cell_states_map[output_index] = -5;
						  output_gate += weight_cg[weight_c_index + 4] * cell_states_map[output_index];	//8.11
						  output_gate = sigmoid(output_gate);	//8.12
						  output_gates_map[output_index] = output_gate;
						  cell_output = output_gate*tanh(cell_states_map[output_index]);	//8.13
						  top_data[output_index] = cell_output;

					  }
				 
			  }

		  }
	  }
	  else if (direction == 2)	//top right
	  {
		  for (int oh = 0; oh < output_height_; ++oh) {
			  for (int ow = output_width_-1; ow >=0; --ow) {
				  
				  int sub_weight_offset_h = hidden_dim_*hidden_dim_;
				  for (int hi = 0; hi < hidden_dim_; hi++)	//hid=num_output
				  {
					  net_input = 0;
					  input_gate = 0;
					  output_gate = 0;
					  forget_gate = 0;
					  cell_states = 0;
					  cell_output = 0;
					  int weight_offset = channels_*kernel_height_*kernel_width_*hi*weight_groups;
					  for (int c = 0; c < channels_; ++c) {
						 
						  int sub_weight_offset = kernel_height_*kernel_width_;
						  int input_offset = c*input_width_*input_height_;
						 

						  int hstart = oh * stride_height_;
						  int wstart = ow * stride_width_;
						  int hend = min(hstart + kernel_height_, input_height_);
						  int wend = min(wstart + kernel_width_, input_width_);
						  hstart = max(hstart, 0);
						  wstart = max(wstart, 0);
						  int weight_index = 0;
						  for (int h = hstart; h < hend; ++h) {
							  int index = h * input_width_;
							  for (int w = wstart; w < wend; ++w) {
								  index += w;

								  const int index = h * input_width_ + w;
								  net_input += weight_ih[weight_index + weight_offset] * bottom_data[index + input_offset];
								  input_gate += weight_ih[weight_index + weight_offset + sub_weight_offset] * bottom_data[index + input_offset];
								  output_gate += weight_ih[weight_index + weight_offset + sub_weight_offset * 2] * bottom_data[index + input_offset];
								  forget_gate += weight_ih[weight_index + weight_offset + sub_weight_offset * 3] * bottom_data[index + input_offset];
								  weight_index++;
							  }
						  }
						  weight_offset += kernel_height_*kernel_width_*weight_groups;
					  }
					  const int output_index = oh * output_width_ + ow + hi*output_height_*output_width_;
					  for (int hj = 0; hj<hidden_dim_; hj++)
					  {
						  if (ow<output_width_ - 1)
							  cell_states_x_1 = cell_states_map[output_index + 1];
						  else
							  cell_states_x_1 = 0;
						  if (oh>0)
							  cell_states_y_1 = cell_states_map[output_index - output_width_];
						  else
							  cell_states_y_1 = 0;
						  if (ow<output_width_ - 1)
							  cell_outputs_x_1 = top_data[output_index + 1];
						  else
							  cell_outputs_x_1 = 0;
						  if (oh>0)
							  cell_outputs_y_1 = top_data[output_index - output_width_];
						  else
							  cell_outputs_y_1 = 0;
						  const int weight_h_index = hi*hidden_dim_ + hj;
						  net_input += weight_hhx[weight_h_index] * cell_outputs_x_1;
						  net_input += weight_hhy[weight_h_index] * cell_outputs_y_1;

						  input_gate += weight_hhx[weight_h_index + sub_weight_offset_h] * cell_outputs_x_1;
						  input_gate += weight_hhy[weight_h_index + sub_weight_offset_h] * cell_outputs_y_1;

						  output_gate += weight_hhx[weight_h_index + sub_weight_offset_h * 2] * cell_outputs_x_1;
						  output_gate += weight_hhy[weight_h_index + sub_weight_offset_h * 2] * cell_outputs_y_1;

						  forget_gate += weight_hhx[weight_h_index + sub_weight_offset_h * 3] * cell_outputs_x_1;
						  forget_gate += weight_hhx[weight_h_index + sub_weight_offset_h * 3] * cell_outputs_y_1;

					  }
					  const int weight_c_index = hi * 5;
					  input_gate += weight_cg[weight_c_index] * cell_states_x_1;
					  input_gate += weight_cg[weight_c_index + 1] * cell_states_y_1;	//8.5

					  input_gate = sigmoid(input_gate);	//8.6
					  input_gates_map[output_index] = input_gate;

					  forget_gate += weight_cg[weight_c_index + 2] * cell_states_x_1;
					  forget_gate += weight_cg[weight_c_index + 3] * cell_states_y_1;	//8.7
					  forget_gate = sigmoid(forget_gate);	//8.8
					  forget_gates_map[output_index] = forget_gate;

					  net_input = tanh(net_input);	//8.9
					  net_inputs_map[output_index] = net_input;
					  cell_states_map[output_index] += input_gate*net_input + forget_gate*cell_states_x_1 + forget_gate*cell_states_y_1;	//8.10
					  if (cell_states_map[output_index] > 5)
						  cell_states_map[output_index] = 5;
					  else if (cell_states_map[output_index] < -5)
						  cell_states_map[output_index] = -5;
					  output_gate += weight_cg[weight_c_index + 4] * cell_states_map[output_index];	//8.11
					  output_gate = sigmoid(output_gate);	//8.12
					  output_gates_map[output_index] = output_gate;
					  cell_output = output_gate*tanh(cell_states_map[output_index]);	//8.13
					  top_data[output_index] = cell_output;

				  }

			  }

		  }
	  }
	  else if (direction == 3)	//bottom left
	  {
		  for (int oh = output_height_-1; oh >=0; --oh) {
			  for (int ow = 0; ow <output_width_; ++ow) {
				  
				  int sub_weight_offset_h = hidden_dim_*hidden_dim_;
				  for (int hi = 0; hi < hidden_dim_; hi++)	//hid=num_output
				  {
					  net_input = 0;
					  input_gate = 0;
					  output_gate = 0;
					  forget_gate = 0;
					  cell_states = 0;
					  cell_output = 0;
					  int weight_offset = channels_*kernel_height_*kernel_width_*hi*weight_groups;
					  for (int c = 0; c < channels_; ++c) {
						  
						  int sub_weight_offset = kernel_height_*kernel_width_;
						  int input_offset = input_width_*input_height_*c;
						  

						  int hstart = oh * stride_height_;
						  int wstart = ow * stride_width_;
						  int hend = min(hstart + kernel_height_, input_height_);
						  int wend = min(wstart + kernel_width_, input_width_);
						  hstart = max(hstart, 0);
						  wstart = max(wstart, 0);
						  int weight_index = 0;
						  for (int h = hstart; h < hend; ++h) {
							  int index = h * input_width_;
							  for (int w = wstart; w < wend; ++w) {
								  index += w;
								  net_input += weight_ih[weight_index + weight_offset] * bottom_data[index + input_offset];
								  input_gate += weight_ih[weight_index + weight_offset + sub_weight_offset] * bottom_data[index + input_offset];
								  output_gate += weight_ih[weight_index + weight_offset + sub_weight_offset * 2] * bottom_data[index + input_offset];
								  forget_gate += weight_ih[weight_index + weight_offset + sub_weight_offset * 3] * bottom_data[index + input_offset];
								  weight_index++;
							  }
						  }
						  weight_offset += kernel_height_*kernel_width_*weight_groups;
					  }
					  const int output_index = oh * output_width_ + ow + hi*output_height_*output_width_;
					  for (int hj = 0; hj<hidden_dim_; hj++)
					  {
						  if (ow>0)
							  cell_states_x_1 = cell_states_map[output_index - 1];
						  else
							  cell_states_x_1 = 0;
						  if (oh<output_height_ - 1)
							  cell_states_y_1 = cell_states_map[output_index + output_width_];
						  else
							  cell_states_y_1 = 0;
						  if (ow>0)
							  cell_outputs_x_1 = top_data[output_index - 1];
						  else
							  cell_outputs_x_1 = 0;
						  if (oh<output_height_ - 1)
							  cell_outputs_y_1 = top_data[output_index + output_width_];
						  else
							  cell_outputs_y_1 = 0;
						  const int weight_h_index = hi*hidden_dim_ + hj;
						  net_input += weight_hhx[weight_h_index] * cell_outputs_x_1;
						  net_input += weight_hhy[weight_h_index] * cell_outputs_y_1;

						  input_gate += weight_hhx[weight_h_index + sub_weight_offset_h] * cell_outputs_x_1;
						  input_gate += weight_hhy[weight_h_index + sub_weight_offset_h] * cell_outputs_y_1;

						  output_gate += weight_hhx[weight_h_index + sub_weight_offset_h * 2] * cell_outputs_x_1;
						  output_gate += weight_hhy[weight_h_index + sub_weight_offset_h * 2] * cell_outputs_y_1;

						  forget_gate += weight_hhx[weight_h_index + sub_weight_offset_h * 3] * cell_outputs_x_1;
						  forget_gate += weight_hhx[weight_h_index + sub_weight_offset_h * 3] * cell_outputs_y_1;

					  }
					  const int weight_c_index = hi * 5;
					  input_gate += weight_cg[weight_c_index] * cell_states_x_1;
					  input_gate += weight_cg[weight_c_index + 1] * cell_states_y_1;	//8.5

					  input_gate = sigmoid(input_gate);	//8.6
					  input_gates_map[output_index] = input_gate;

					  forget_gate += weight_cg[weight_c_index + 2] * cell_states_x_1;
					  forget_gate += weight_cg[weight_c_index + 3] * cell_states_y_1;	//8.7
					  forget_gate = sigmoid(forget_gate);	//8.8
					  forget_gates_map[output_index] = forget_gate;

					  net_input = tanh(net_input);	//8.9
					  net_inputs_map[output_index] = net_input;
					  cell_states_map[output_index] += input_gate*net_input + forget_gate*cell_states_x_1 + forget_gate*cell_states_y_1;	//8.10
					  if (cell_states_map[output_index] > 5)
						  cell_states_map[output_index] = 5;
					  else if (cell_states_map[output_index] < -5)
						  cell_states_map[output_index] = -5;
					  output_gate += weight_cg[weight_c_index + 4] * cell_states_map[output_index];	//8.11
					  output_gate = sigmoid(output_gate);	//8.12
					  output_gates_map[output_index] = output_gate;
					  cell_output = output_gate*tanh(cell_states_map[output_index]);	//8.13
					  top_data[output_index] = cell_output;

				  }

			  }

		  }
	  }
	  else if (direction == 4)	//bottom right
	  {
		  for (int oh = output_height_-1; oh >= 0; --oh) {
			  for (int ow = output_width_-1; ow >=0; --ow) {
				 
				  int sub_weight_offset_h = hidden_dim_*hidden_dim_;
				  for (int hi = 0; hi < hidden_dim_; hi++)	//hid=num_output
				  {
					  net_input = 0;
					  input_gate = 0;
					  output_gate = 0;
					  forget_gate = 0;
					  cell_states = 0;
					  cell_output = 0;
					  int weight_offset = channels_*kernel_height_*kernel_width_*hi*weight_groups;
					  for (int c = 0; c < channels_; ++c) {
						  
						  int sub_weight_offset = kernel_height_*kernel_width_;
						  int input_offset = input_width_*input_height_*c;
						 

						  int hstart = oh * stride_height_;
						  int wstart = ow * stride_width_;
						  int hend = min(hstart + kernel_height_, input_height_);
						  int wend = min(wstart + kernel_width_, input_width_);
						  hstart = max(hstart, 0);
						  wstart = max(wstart, 0);
						  int weight_index = 0;
						  for (int h = hstart; h < hend; ++h) {
							  int index = h * input_width_;
							  for (int w = wstart; w < wend; ++w) {
								  index += w;
								  net_input += weight_ih[weight_index + weight_offset]*bottom_data[index + input_offset];
								  input_gate += weight_ih[weight_index + weight_offset + sub_weight_offset] * bottom_data[index + input_offset];
								  output_gate += weight_ih[weight_index + weight_offset + sub_weight_offset * 2] * bottom_data[index + input_offset];
								  forget_gate += weight_ih[weight_index + weight_offset + sub_weight_offset * 3] * bottom_data[index + input_offset];
								  weight_index++;
							  }
						  }
						  weight_offset += kernel_height_*kernel_width_*weight_groups;
					  }
					  const int output_index = oh * output_width_ + ow + hi*output_height_*output_width_;
					  for (int hj = 0; hj<hidden_dim_; hj++)
					  {
						  if (ow<output_width_-1)
							  cell_states_x_1 = cell_states_map[output_index + 1];
						  else
							  cell_states_x_1 = 0;
						  if (oh<output_height_-1)
							  cell_states_y_1 = cell_states_map[output_index + output_width_];
						  else
							  cell_states_y_1 = 0;
						  if (ow<output_width_ - 1)
							  cell_outputs_x_1 = top_data[output_index + 1];
						  else
							  cell_outputs_x_1 = 0;
						  if (oh<output_height_ - 1)
							  cell_outputs_y_1 = top_data[output_index + output_width_];
						  else
							  cell_outputs_y_1 = 0;
						  const int weight_h_index = hi*hidden_dim_ + hj;
						  net_input += weight_hhx[weight_h_index] * cell_outputs_x_1;
						  net_input += weight_hhy[weight_h_index] * cell_outputs_y_1;

						  input_gate += weight_hhx[weight_h_index + sub_weight_offset_h] * cell_outputs_x_1;
						  input_gate += weight_hhy[weight_h_index + sub_weight_offset_h] * cell_outputs_y_1;

						  output_gate += weight_hhx[weight_h_index + sub_weight_offset_h * 2] * cell_outputs_x_1;
						  output_gate += weight_hhy[weight_h_index + sub_weight_offset_h * 2] * cell_outputs_y_1;

						  forget_gate += weight_hhx[weight_h_index + sub_weight_offset_h * 3] * cell_outputs_x_1;
						  forget_gate += weight_hhx[weight_h_index + sub_weight_offset_h * 3] * cell_outputs_y_1;

					  }
					  const int weight_c_index = hi * 5;
					  input_gate += weight_cg[weight_c_index] * cell_states_x_1;
					  input_gate += weight_cg[weight_c_index + 1] * cell_states_y_1;	//8.5

					  input_gate = sigmoid(input_gate);	//8.6
					  input_gates_map[output_index] = input_gate;

					  forget_gate += weight_cg[weight_c_index + 2] * cell_states_x_1;
					  forget_gate += weight_cg[weight_c_index + 3] * cell_states_y_1;	//8.7
					  forget_gate = sigmoid(forget_gate);	//8.8
					  forget_gates_map[output_index] = forget_gate;

					  net_input = tanh(net_input);	//8.9
					  net_inputs_map[output_index] = net_input;
					  cell_states_map[output_index] += input_gate*net_input + forget_gate*cell_states_x_1 + forget_gate*cell_states_y_1;	//8.10
					 
					  if (cell_states_map[output_index] > 5)
						  cell_states_map[output_index] = 5;
					  else if (cell_states_map[output_index] < -5)
						  cell_states_map[output_index] = -5;
					  /*if (cell_states_map[output_index] != cell_states_map[output_index])
					  {
						  Dtype tempdouble = cell_states_map[output_index];
						  tempdouble = cell_states_map[output_index + 1];
						  tempdouble = cell_states_map[output_index + output_width_];
					  }*/
					  output_gate += weight_cg[weight_c_index + 4] * cell_states_map[output_index];	//8.11
					  output_gate = sigmoid(output_gate);	//8.12
					  output_gates_map[output_index] = output_gate;
					  cell_output = output_gate*tanh(cell_states_map[output_index]);	//8.13
					  top_data[output_index] = cell_output;
					  if (abs(top_data[output_index] > 10))
						  int tempint = 0;
				  }
				//  printf("x:%d y:%d\n", ow, oh);
			  }

		  }
		  //for (int hh = 0; hh < hidden_dim_; hh++)
		  //{
			 // tempchar[0] = '\0';
			 // sprintf(tempchar, "cell_states_map%d_%d.txt", n, hh);
			 // FILE* fp = fopen(tempchar, "w");
			 // for (int i = 0; i < output_height_; i++)
			 // {
				//  for (int j = 0; j < output_width_; j++)
				//  {
				//	  const int output_index = i * output_width_ + j + hh*output_width_*output_height_;
				//	  fprintf(fp, "%f\t", cell_states_map[output_index]);
				//  }
				//  fprintf(fp, "\n");
			 // }
			 // fclose(fp);
		  //}
		  //for (int hh = 0; hh < hidden_dim_; hh++)
		  //{
			 // tempchar[0] = '\0';
			 // sprintf(tempchar, "cell_input%d_%d.txt", n, hh);
			 // FILE* fp = fopen(tempchar, "w");
			 // for (int i = 0; i < output_height_; i++)
			 // {
				//  for (int j = 0; j < output_width_; j++)
				//  {
				//	  const int output_index = i * output_width_ + j + hh*output_width_*output_height_;
				//	  fprintf(fp, "%f\t", net_inputs_map[output_index]);
				//  }
				//  fprintf(fp, "\n");
			 // }
			 // fclose(fp);
		  //}
		  //for (int hh = 0; hh < hidden_dim_; hh++)
		  //{
			 // tempchar[0] = '\0';
			 // sprintf(tempchar, "cell_output%d_%d.txt", n, hh);
			 // FILE* fp = fopen(tempchar, "w");
			 // for (int i = 0; i < output_height_; i++)
			 // {
				//  for (int j = 0; j < output_width_; j++)
				//  {
				//	  const int output_index = i * output_width_ + j + hh*output_width_*output_height_;
				//	  fprintf(fp, "%f\t", top_data[output_index]);
				//  }
				//  fprintf(fp, "\n");
			 // }
			 // fclose(fp);
		  //}
		  //tempchar[0] = '\0';
		  //for (int c = 0; c < channels_; c++)
		  //{
			 // sprintf(tempchar, "input%d_%d.txt", n, c);
			 // FILE* fp = fopen(tempchar, "w");
			 // for (int i = 0; i < input_height_; i++)
			 // {
				//  for (int j = 0; j < input_width_; j++)
				//  {
				//	  const int input_index = i * input_width_ + j + c*input_width_*input_height_;
				//	  fprintf(fp, "%f\t", bottom_data[input_index]);
				//  }
				//  fprintf(fp, "\n");
			 // }
			 // fclose(fp);
		  //}
		  /*FILE* fp;
		  tempchar[0] = '\0';
		  sprintf(tempchar, "top_data%d.txt", n);
		  fopen_s(&fp, tempchar, "w");
		  int tempcount = 0;
		  for (int i = 0; i < output_height_; i++)
		  {
			  for (int j = 0; j < output_width_; j++)
			  {
				  fprintf(fp, "%f\t", top_data[tempcount]);
				  tempcount++;
			  }
			  fprintf(fp, "\n");
		  }
		  fclose(fp);*/
	  }
	  
	  bottom_data += bottom[0]->offset(1, 0);
	  top_data += top[0]->offset(1, 0);
	  cell_states_map += top[0]->offset(1, 0);
	  input_gates_map += top[0]->offset(1, 0);
	  output_gates_map += top[0]->offset(1, 0);
	  forget_gates_map += top[0]->offset(1, 0);
	  net_inputs_map += top[0]->offset(1, 0);
	 
  }
  bottom_data -= bottom[0]->offset(bottom[0]->num(), 0);
  top_data -= top[0]->offset(top[0]->num(), 0);
  cell_states_map -= top[0]->offset(top[0]->num(), 0);
  input_gates_map -= top[0]->offset(top[0]->num(), 0);
  output_gates_map -= top[0]->offset(top[0]->num(), 0);
  forget_gates_map -= top[0]->offset(top[0]->num(), 0);
  net_inputs_map -= top[0]->offset(top[0]->num(), 0);
 /* FILE* fp;
  fopen_s(&fp, "weight_ih.txt", "w");
  int weight_index = 0;
  int sub_weight_offset = 0;
  int sub_weight_offset_h = 0;
  for (int hi = 0; hi < hidden_dim_; hi++)
  {
	  int weight_offset = channels_*kernel_height_*kernel_width_*hi*weight_groups;
	  for (int c = 0; c < channels_; ++c)
	  {
		  weight_index = 0;
		  for (int h = 0; h < kernel_height_; ++h) {
			  for (int w = 0; w < kernel_width_; ++w) {
				  fprintf(fp, "%f\t", weight_ih[weight_index + weight_offset]);
				  weight_index++;
			  }
			  fprintf(fp, "\n");
		  }
		  weight_offset += kernel_height_*kernel_width_*weight_groups;
	  }
	  fprintf(fp, "\n");
	  weight_offset = channels_*kernel_height_*kernel_width_*hi*weight_groups;
	  for (int c = 0; c < channels_; ++c)
	  {
		  weight_index = 0;
		  for (int h = 0; h < kernel_height_; ++h) {
			  for (int w = 0; w < kernel_width_; ++w) {
				  fprintf(fp, "%f\t", weight_ih[weight_index + weight_offset + sub_weight_offset]);
				  weight_index++;
			  }
			  fprintf(fp, "\n");
		  }
		  weight_offset += kernel_height_*kernel_width_*weight_groups;
	  }
	  fprintf(fp, "\n");
	  weight_offset = channels_*kernel_height_*kernel_width_*hi*weight_groups;
	  for (int c = 0; c < channels_; ++c)
	  {
		  weight_index = 0;
		  for (int h = 0; h < kernel_height_; ++h) {
			  int index = h * kernel_width_;
			  for (int w = 0; w < kernel_width_; ++w) {
				  index += w;
				  fprintf(fp, "%f\t", weight_ih[weight_index + weight_offset + sub_weight_offset * 2]);
				  weight_index++;
			  }
			  fprintf(fp, "\n");
		  }
		  weight_offset += kernel_height_*kernel_width_*weight_groups;
	  }
	  fprintf(fp, "\n");
	  weight_offset = channels_*kernel_height_*kernel_width_*hi*weight_groups;
	  for (int c = 0; c < channels_; ++c)
	  {
		  weight_index = 0;
		  for (int h = 0; h < kernel_height_; ++h) {
			  for (int w = 0; w < kernel_width_; ++w) {
				  fprintf(fp, "%f\t", weight_ih[weight_index + weight_offset + sub_weight_offset * 3]);
				  weight_index++;
			  }
			  fprintf(fp, "\n");
		  }
		  weight_offset += kernel_height_*kernel_width_*weight_groups;
	  }
  }

  fclose(fp);
  fopen_s(&fp, "weight_hhx.txt", "w");

  for (int hi = 0; hi < hidden_dim_; hi++)
  {
	  for (int hj = 0; hj<hidden_dim_; hj++)
	  {
		  const int weight_h_index = hi*hidden_dim_ + hj;
		  fprintf(fp, "%f\t", weight_hhx[weight_h_index]);
	  }
	  fprintf(fp, "\n");
  }
  for (int hi = 0; hi < hidden_dim_; hi++)
  {
	  for (int hj = 0; hj<hidden_dim_; hj++)
	  {
		  const int weight_h_index = hi*hidden_dim_ + hj;
		  fprintf(fp, "%f\t", weight_hhx[weight_h_index + sub_weight_offset_h]);
	  }
	  fprintf(fp, "\n");
  }
  for (int hi = 0; hi < hidden_dim_; hi++)
  {
	  for (int hj = 0; hj<hidden_dim_; hj++)
	  {
		  const int weight_h_index = hi*hidden_dim_ + hj;
		  fprintf(fp, "%f\t", weight_hhx[weight_h_index + sub_weight_offset_h * 2]);
	  }
	  fprintf(fp, "\n");
  }
  for (int hi = 0; hi < hidden_dim_; hi++)
  {
	  for (int hj = 0; hj<hidden_dim_; hj++)
	  {
		  const int weight_h_index = hi*hidden_dim_ + hj;
		  fprintf(fp, "%f\t", weight_hhx[weight_h_index + sub_weight_offset_h * 3]);
	  }
	  fprintf(fp, "\n");
  }
  fclose(fp);
  fopen_s(&fp, "weight_hhy.txt", "w");
  for (int hi = 0; hi < hidden_dim_; hi++)
  {
	  for (int hj = 0; hj<hidden_dim_; hj++)
	  {
		  const int weight_h_index = hi*hidden_dim_ + hj;
		  fprintf(fp, "%f\t", weight_hhy[weight_h_index]);
	  }
	  fprintf(fp, "\n");
  }
  for (int hi = 0; hi < hidden_dim_; hi++)
  {
	  for (int hj = 0; hj<hidden_dim_; hj++)
	  {
		  const int weight_h_index = hi*hidden_dim_ + hj;
		  fprintf(fp, "%f\t", weight_hhy[weight_h_index + sub_weight_offset_h]);
	  }
	  fprintf(fp, "\n");
  }
  for (int hi = 0; hi < hidden_dim_; hi++)
  {
	  for (int hj = 0; hj<hidden_dim_; hj++)
	  {
		  const int weight_h_index = hi*hidden_dim_ + hj;
		  fprintf(fp, "%f\t", weight_hhy[weight_h_index + sub_weight_offset_h * 2]);
	  }
	  fprintf(fp, "\n");
  }
  for (int hi = 0; hi < hidden_dim_; hi++)
  {
	  for (int hj = 0; hj<hidden_dim_; hj++)
	  {
		  const int weight_h_index = hi*hidden_dim_ + hj;
		  fprintf(fp, "%f\t", weight_hhy[weight_h_index + sub_weight_offset_h * 3]);
	  }
	  fprintf(fp, "\n");
  }

  fclose(fp);
  fopen_s(&fp, "weight_cg.txt", "w");
  for (int hi = 0; hi < hidden_dim_; hi++)
  {
	  for (int hj = 0; hj<5; hj++)
	  {
		  const int weight_h_index = hi*hidden_dim_ + hj;
		  fprintf(fp, "%f\t", weight_cg[weight_h_index]);
	  }
	  fprintf(fp, "\n");
  }
  fclose(fp);
  for (int n = 0; n < bottom[0]->num(); n++)
  {
	  tempchar[0] = '\0';
	  sprintf(tempchar, "cell_states_map%d.txt", n);
	  fopen_s(&fp, tempchar, "w");
	  for (int h = 0; h < hidden_dim_; h++)
	  for (int i = 0; i < output_height_; i++)
	  {
		  for (int j = 0; j < output_width_; j++)
		  {
			  fprintf(fp, "%f\t", *cell_states_map);
			  cell_states_map++;
		  }
		  fprintf(fp, "\n");
	  }
	  fclose(fp);
	  tempchar[0] = '\0';
	  sprintf(tempchar, "input_gates_map%d.txt", n);
	  fopen_s(&fp, tempchar, "w");
	  for (int h = 0; h < hidden_dim_; h++)
	  for (int i = 0; i < output_height_; i++)
	  {
		  for (int j = 0; j < output_width_; j++)
		  {
			  fprintf(fp, "%f\t", *input_gates_map);
			  input_gates_map++;
		  }
		  fprintf(fp, "\n");
	  }
	  fclose(fp);
	  tempchar[0] = '\0';
	  sprintf(tempchar, "output_gates_map%d.txt", n);
	  fopen_s(&fp, tempchar, "w");
	  for (int h = 0; h < hidden_dim_; h++)
	  for (int i = 0; i < output_height_; i++)
	  {
		  for (int j = 0; j < output_width_; j++)
		  {
			  fprintf(fp, "%f\t", *output_gates_map);
			  output_gates_map++;
		  }
		  fprintf(fp, "\n");
	  }
	  fclose(fp);
	  tempchar[0] = '\0';
	  sprintf(tempchar, "forget_gates_map%d.txt", n);
	  fopen_s(&fp, tempchar, "w");
	  for (int h = 0; h < hidden_dim_; h++)
	  for (int i = 0; i < output_height_; i++)
	  {
		  for (int j = 0; j < output_width_; j++)
		  {
			  fprintf(fp, "%f\t", *forget_gates_map);
			  forget_gates_map++;
		  }
		  fprintf(fp, "\n");
	  }
	  fclose(fp);

	  tempchar[0] = '\0';
	  sprintf(tempchar, "top_data%d.txt", n);
	  fopen_s(&fp, tempchar, "w");
	  for (int h = 0; h < hidden_dim_; h++)
	  {
		  for (int i = 0; i < output_height_; i++)
		  {
			  for (int j = 0; j < output_width_; j++)
			  {
				  fprintf(fp, "%f\t", *top_data);
				  top_data++;
			  }
			  fprintf(fp, "\n");
		  }
	  }
	  fclose(fp);
	  tempchar[0] = '\0';
	  sprintf(tempchar, "bottom_data%d.txt", n);
	  fopen_s(&fp, tempchar, "w");
	  for (int c = 0; c < channels_; c++)
	  {
		  for (int i = 0; i < input_height_; i++)
		  {
			  for (int j = 0; j < input_width_; j++)
			  {
				  fprintf(fp, "%f\t", *bottom_data);
				  bottom_data++;
			  }
			  fprintf(fp, "\n");
		  }
	  }
	  fclose(fp);


  }*/
  //const int num = bottom[0]->shape(1);
  //const int x_dim = hidden_dim_ * 4;
  //const Dtype* C_prev = bottom[0]->cpu_data();
  //const Dtype* X = bottom[1]->cpu_data();
  //const Dtype* cont = bottom[2]->cpu_data();
  //Dtype* C = top[0]->mutable_cpu_data();
  //Dtype* H = top[1]->mutable_cpu_data();
  //for (int n = 0; n < num; ++n) {
  //  for (int d = 0; d < hidden_dim_; ++d) {
  //    const Dtype i = sigmoid(X[d]);
  //    const Dtype f = (*cont == 0) ? 0 :
  //        (*cont * sigmoid(X[1 * hidden_dim_ + d]));
  //    const Dtype o = sigmoid(X[2 * hidden_dim_ + d]);
  //    const Dtype g = tanh(X[3 * hidden_dim_ + d]);
  //    const Dtype c_prev = C_prev[d];
  //    const Dtype c = f * c_prev + i * g;
  //    C[d] = c;
  //    const Dtype tanh_c = tanh(c);
  //    H[d] = o * tanh_c;
  //  }
  //  C_prev += hidden_dim_;
  //  X += x_dim;
  //  C += hidden_dim_;
  //  H += hidden_dim_;
  //  ++cont;
  //}
}

template <typename Dtype>
void LSTMUnitLayer<Dtype>::Backward_cpu(const vector<Blob<Dtype>*>& top,
    const vector<bool>& propagate_down, const vector<Blob<Dtype>*>& bottom) {
  CHECK(!propagate_down[0]) << "Cannot backpropagate to sequence indicators.";
  const Dtype* top_diff = top[0]->cpu_diff();
  const Dtype* bottom_data = bottom[0]->cpu_data();
  const Dtype* top_data = top[0]->cpu_data();
  Dtype* bottom_diff = bottom[0]->mutable_cpu_diff();
  //Dtype* cell_outputs_diff = cell_outputs_diff_.mutable_cpu_data();
  Dtype* cell_states_diff = cell_states_diff_.mutable_cpu_data();
  Dtype* input_gates_diff = input_gates_diff_.mutable_cpu_data();
  Dtype* output_gates_diff = output_gates_diff_.mutable_cpu_data();
  Dtype* forget_gates_diff = forget_gates_diff_.mutable_cpu_data();
  const Dtype* cell_states_map = cell_states_map_.cpu_data();
  const Dtype* input_gates_map = input_gates_map_.cpu_data();
  const Dtype* output_gates_map = output_gates_map_.cpu_data();
  const Dtype* forget_gates_map = forget_gates_map_.cpu_data();
  const Dtype* net_inputs_map = net_inputs_map_.cpu_data();
  Dtype cell_outputs_diff_x1 = 0;
  Dtype cell_outputs_diff_y1 = 0;
  Dtype cell_states_diff_x1 = 0;
  Dtype cell_states_diff_y1 = 0;
  Dtype cell_outputs_diff = 0;
  Dtype input_gate_diff1 = 0;
  Dtype output_gate_diff = 0;
  Dtype forget_gate_diff1 = 0;
  Dtype cell_states_x1 = 0;
  Dtype cell_states_y1 = 0;
  Dtype forget_gate1 = 0;
  Dtype cell_input_diff = 0;
  Dtype input_gate_diff_x1 = 0;
  Dtype input_gate_diff_y1 = 0;
  Dtype output_gate_diff_x1 = 0;
  Dtype output_gate_diff_y1 = 0;
  Dtype forget_gate_diff_x1 = 0;
  Dtype forget_gate_diff_y1 = 0;
  Dtype forget_gate_x1 = 0;
  Dtype forget_gate_y1 = 0;
  Dtype cell_states_x_1 = 0;
  Dtype cell_states_y_1 = 0;
  Dtype cell_outputs_x_1 = 0;
  Dtype cell_outputs_y_1 = 0;
  const Dtype* weight_ih = this->blobs_[0]->cpu_data();
  const Dtype* weight_hhx = this->blobs_[1]->cpu_data();
  const Dtype* weight_hhy = this->blobs_[2]->cpu_data();
  const Dtype* weight_cg = this->blobs_[3]->cpu_data();
  int bottomcount = bottom[0]->count();
  int topcount = top[0]->count();

  caffe_set(topcount, Dtype(0), cell_states_diff);
  caffe_set(topcount, Dtype(0), input_gates_diff);
  caffe_set(topcount, Dtype(0), output_gates_diff);
  caffe_set(topcount, Dtype(0), forget_gates_diff);
  Dtype* dw_ih = this->blobs_[0]->mutable_cpu_diff();
  Dtype* dw_hhx = this->blobs_[1]->mutable_cpu_diff();
  Dtype* dw_hhy = this->blobs_[2]->mutable_cpu_diff();
  Dtype* dw_cg = this->blobs_[3]->mutable_cpu_diff();
  switch (this->layer_param_.lstm_param().direction())
  {
  case 1:	//top left
	  for (int n = 0; n < top[0]->num(); ++n) {
		  for (int oh = output_height_ - 1; oh >= 0; --oh) {
			  for (int ow = output_width_ - 1; ow >= 0; --ow){
				  for (int hi = 0; hi < hidden_dim_; hi++)	//hid=num_output
				  {
					  const int output_index = oh * output_width_ + ow + hi*output_height_*output_width_;
					  if (ow<output_width_ - 1)
						  cell_outputs_diff_x1 = top_diff[output_index + 1];
					  else
						  cell_outputs_diff_x1 = 0;
					  if (oh<output_height_ - 1)
						  cell_outputs_diff_y1 = top_diff[output_index + output_width_];
					  else
						  cell_outputs_diff_y1 = 0;
					  if (ow<output_width_ - 1)
						  cell_states_diff_x1 = cell_states_diff[output_index + 1];
					  else
						  cell_states_diff_x1 = 0;
					  if (oh<output_height_ - 1)
						  cell_states_diff_y1 = cell_states_diff[output_index + output_width_];
					  else
						  cell_states_diff_y1 = 0;
					  if (ow<output_width_ - 1)
						  input_gate_diff_x1 = input_gates_diff[output_index + 1];
					  else
						  input_gate_diff_x1 = 0;
					  if (oh<output_height_ - 1)
						  input_gate_diff_y1 = input_gates_diff[output_index + output_width_];
					  else
						  input_gate_diff_y1 = 0;
					  if (ow<output_width_ - 1)
						  forget_gate_diff_x1 = forget_gates_diff[output_index + 1];
					  else
						  forget_gate_diff_x1 = 0;
					  if (oh<output_height_ - 1)
						  forget_gate_diff_y1 = forget_gates_diff[output_index + output_width_];
					  else
						  forget_gate_diff_y1 = 0;
					  if (ow<output_width_ - 1)
						  forget_gate_x1 = forget_gates_map[output_index + 1];
					  else
						  forget_gate_x1 = 0;
					  if (oh<output_height_ - 1)
						  forget_gate_y1 = forget_gates_map[output_index + output_width_];
					  else
						  forget_gate_y1 = 0;

					  if (ow<output_width_ - 1)
						  cell_states_x1 = cell_states_map[output_index + 1];
					  else
						  cell_states_x1 = 0;
					  if (oh<output_height_ - 1)
						  cell_states_y1 = cell_states_map[output_index + output_width_];
					  else
						  cell_states_y1 = 0;
					  if (ow>0)
						  cell_states_x_1 = cell_states_map[output_index - 1];
					  else
						  cell_states_x_1 = 0;
					  if (oh>0)
						  cell_states_y_1 = cell_states_map[output_index - output_width_];
					  else
						  cell_states_y_1 = 0;
					  if (ow>0)
						  cell_outputs_x_1 = top_data[output_index - 1];
					  else
						  cell_outputs_x_1 = 0;
					  if (oh>0)
						  cell_outputs_y_1 = top_data[output_index - output_width_];
					  else
						  cell_outputs_y_1 = 0;
					  cell_outputs_diff = top_diff[output_index];
					  //need adding hstart
					  const int sub_weight_offset = kernel_height_*kernel_width_;
					  const int sub_weight_offset_h = hidden_dim_*hidden_dim_;
					  
					  const int weight_c_index = hi * 5;
					  for (int hj = 0; hj<hidden_dim_; hj++)
					  {
						  
						  const int weight_h_index = hi*hidden_dim_ + hj;
						 
						  
						  cell_outputs_diff += weight_hhx[weight_h_index] * cell_outputs_diff_x1;
						  cell_outputs_diff += weight_hhy[weight_h_index] * cell_outputs_diff_y1;	
						  cell_outputs_diff += weight_hhx[weight_h_index + sub_weight_offset_h] * input_gate_diff_x1;
						  cell_outputs_diff += weight_hhy[weight_h_index + sub_weight_offset_h] * input_gate_diff_y1;
						  cell_outputs_diff += weight_hhx[weight_h_index + sub_weight_offset_h*2] * output_gate_diff_x1;
						  cell_outputs_diff += weight_hhy[weight_h_index + sub_weight_offset_h*2] * output_gate_diff_y1;
						  cell_outputs_diff += weight_hhx[weight_h_index + sub_weight_offset_h*3] * forget_gate_diff_x1;
						  cell_outputs_diff += weight_hhy[weight_h_index + sub_weight_offset_h*3] * forget_gate_diff_y1;	//Equation 8.15
					  }
					  output_gates_diff[output_index] = cell_outputs_diff*tanh(cell_states_map[output_index])*dsigmoid(output_gates_map[output_index]);	//Equation 8.16

					  cell_states_diff[output_index] = output_gates_map[output_index] * dtanh(top_data[output_index])*cell_outputs_diff;
					  cell_states_diff[output_index] += weight_cg[weight_c_index] * input_gate_diff_x1;
					  cell_states_diff[output_index] += weight_cg[weight_c_index + 1] * input_gate_diff_y1;
					  
					  cell_states_diff[output_index] += weight_cg[weight_c_index + 2] * forget_gate_diff_x1;
					  cell_states_diff[output_index] += weight_cg[weight_c_index + 3] * forget_gate_diff_y1;
					  cell_states_diff[output_index] += weight_cg[weight_c_index + 4] * output_gate_diff;
					  cell_states_diff[output_index] += forget_gate_x1*cell_states_x1;
					  cell_states_diff[output_index] += forget_gate_y1*cell_states_y1;//Equation 8.17
					  cell_input_diff = input_gates_map[output_index] * dtanh(net_inputs_map[output_index])*cell_states_diff[output_index];	//Equation 8.18
					  forget_gates_diff[output_index] = dsigmoid(forget_gates_map[output_index])*cell_states_diff[output_index] * (cell_states_x_1 + cell_states_y_1);	//Equation 8.19
					  input_gates_diff[output_index] = dsigmoid(input_gates_map[output_index])*cell_states_diff[output_index] * net_inputs_map[output_index];	//Eqaaution 8.20

					  int hstart = oh * stride_height_;
					  int wstart = ow * stride_width_;
					  int hend = min(hstart + kernel_height_, input_height_);
					  int wend = min(wstart + kernel_width_, input_width_);
					  hstart = max(hstart, 0);
					  wstart = max(wstart, 0);
					  
					  int weight_offset = kernel_height_*kernel_width_*hi*channels_*weight_groups;
					  for (int c = 0; c < channels_; ++c)
					  {
						  int weight_index = 0;
						  for (int h = hstart; h < hend; ++h) {
							  for (int w = wstart; w < wend; ++w) {
								  int index = h * input_width_ + c*input_height_*input_width_ + w;
								  dw_ih[weight_index + weight_offset] += bottom_data[index] * cell_input_diff;
								  dw_ih[weight_index + weight_offset + sub_weight_offset] += bottom_data[index] * input_gates_diff[output_index];
								  dw_ih[weight_index + weight_offset + sub_weight_offset * 2] += bottom_data[index] * output_gates_diff[output_index];
								  dw_ih[weight_index + weight_offset + sub_weight_offset * 3] += bottom_data[index] * forget_gates_diff[output_index];
								  bottom_diff[index] += weight_ih[weight_index + weight_offset] * cell_input_diff;
								  bottom_diff[index] += weight_ih[weight_index + weight_offset + sub_weight_offset] * input_gates_diff[output_index];
								  bottom_diff[index] += weight_ih[weight_index + weight_offset + sub_weight_offset * 2] * output_gates_diff[output_index];
								  bottom_diff[index] += weight_ih[weight_index + weight_offset + sub_weight_offset * 3] * forget_gates_diff[output_index];
								  weight_index++;
							  }
						  }
						  weight_offset += kernel_height_*kernel_width_*weight_groups;
					  }
						  
					 
					 
					  for (int hj = 0; hj < hidden_dim_; hj++)
					  {
						  const int weight_h_index = hj*hidden_dim_ + hi;
						  dw_hhx[weight_h_index] += cell_input_diff*cell_outputs_x_1;
						  dw_hhy[weight_h_index] += cell_input_diff*cell_outputs_y_1;

						  dw_hhx[weight_h_index + sub_weight_offset_h] += input_gates_diff[output_index] * cell_outputs_x_1;
						  dw_hhy[weight_h_index + sub_weight_offset_h] += input_gates_diff[output_index] * cell_outputs_y_1;

						  dw_hhx[weight_h_index + sub_weight_offset_h * 2] += output_gates_diff[output_index] * cell_outputs_x_1;
						  dw_hhy[weight_h_index + sub_weight_offset_h * 2] += output_gates_diff[output_index] * cell_outputs_y_1;

						  dw_hhx[weight_h_index + sub_weight_offset_h * 3] += forget_gates_diff[output_index] * cell_outputs_x_1;
						  dw_hhy[weight_h_index + sub_weight_offset_h * 3] += forget_gates_diff[output_index] * cell_outputs_y_1;


					  }
					  
					  dw_cg[hi * 5] += cell_states_x_1 * input_gates_diff[output_index];
					  dw_cg[hi * 5 + 1] += cell_states_y_1* input_gates_diff[output_index];
					  dw_cg[hi * 5 + 2] += cell_states_x_1 * forget_gates_diff[output_index];
					  dw_cg[hi * 5 + 3] += cell_states_y_1* forget_gates_diff[output_index];
					  dw_cg[hi * 5 + 4] += cell_states_map[output_index] * output_gates_diff[output_index];

				  }


			  }
		  
			 
		  }
		  top_data += top[0]->offset(1, 0);
		  top_diff += top[0]->offset(1, 0);
		  cell_states_map += top[0]->offset(1, 0);
		  input_gates_map += top[0]->offset(1, 0);
		  output_gates_map += top[0]->offset(1, 0);
		  forget_gates_map += top[0]->offset(1, 0);
		  net_inputs_map += top[0]->offset(1, 0);
		  cell_states_diff += top[0]->offset(1, 0);
		  input_gates_diff += top[0]->offset(1, 0);
		  output_gates_diff += top[0]->offset(1, 0);
		  forget_gates_diff += top[0]->offset(1, 0);
		  bottom_diff += bottom[0]->offset(1, 0);
		  bottom_data += bottom[0]->offset(1, 0);
	  }
	  
	  break;
  case 2:	//top right
	  for (int n = 0; n < top[0]->num(); ++n) {
		  for (int oh = output_height_ - 1; oh >= 0; --oh) {
			  for (int ow = 0; ow <output_width_; ow++){
				  for (int hi = 0; hi < hidden_dim_; hi++)	//hid=num_output
				  {
					  const int output_index = oh * output_width_ + ow + hi*output_height_*output_width_ ;
					  if (ow>0)
						  cell_outputs_diff_x1 = top_diff[output_index - 1];
					  else
						  cell_outputs_diff_x1 = 0;
					  if (oh<output_height_ - 1)
						  cell_outputs_diff_y1 = top_diff[output_index + output_width_];
					  else
						  cell_outputs_diff_y1 = 0;
					  if (ow>0)
						  cell_states_diff_x1 = cell_states_diff[output_index - 1];
					  else
						  cell_states_diff_x1 = 0;
					  if (oh<output_height_ - 1)
						  cell_states_diff_y1 = cell_states_diff[output_index + output_width_];
					  else
						  cell_states_diff_y1 = 0;
					  if (ow>0)
						  input_gate_diff_x1 = input_gates_diff[output_index - 1];
					  else
						  input_gate_diff_x1 = 0;
					  if (oh<output_height_ - 1)
						  input_gate_diff_y1 = input_gates_diff[output_index + output_width_];
					  else
						  input_gate_diff_y1 = 0;
					  if (ow>0)
						  output_gate_diff_x1 = output_gates_diff[output_index - 1];
					  else
						  output_gate_diff_x1 = 0;
					  if (oh<output_height_ - 1)
						  output_gate_diff_y1 = output_gates_diff[output_index + output_width_];
					  else
						  output_gate_diff_y1 = 0;
					  if (ow>0)
						  forget_gate_diff_x1 = forget_gates_diff[output_index - 1];
					  else
						  forget_gate_diff_x1 = 0;
					  if (oh<output_height_ - 1)
						  forget_gate_diff_y1 = forget_gates_diff[output_index + output_width_];
					  else
						  forget_gate_diff_y1 = 0;
					  if (ow>0)
						  forget_gate_x1 = forget_gates_map[output_index - 1];
					  else
						  forget_gate_x1 = 0;
					  if (oh<output_height_ - 1)
						  forget_gate_y1 = forget_gates_map[output_index + output_width_];
					  else
						  forget_gate_y1 = 0;

					  if (ow>0)
						  cell_states_x1 = cell_states_map[output_index - 1];
					  else
						  cell_states_x1 = 0;
					  if (oh<output_height_ - 1)
						  cell_states_y1 = cell_states_map[output_index + output_width_];
					  else
						  cell_states_y1 = 0;
					  if (ow<output_width_ - 1)
						  cell_states_x_1 = cell_states_map[output_index + 1];
					  else
						  cell_states_x_1 = 0;
					  if (oh>0)
						  cell_states_y_1 = cell_states_map[output_index - output_width_];
					  else
						  cell_states_y_1 = 0;
					  if (ow<output_width_ - 1)
						  cell_outputs_x_1 = top_data[output_index + 1];
					  else
						  cell_outputs_x_1 = 0;
					  if (oh>0)
						  cell_outputs_y_1 = top_data[output_index - output_width_];
					  else
						  cell_outputs_y_1 = 0;
					  cell_outputs_diff = top_diff[output_index];
					  //need adding hstart
					  const int sub_weight_offset = kernel_height_*kernel_width_;
					  const int sub_weight_offset_h = hidden_dim_*hidden_dim_;

					  const int weight_c_index = hi * 5;
					  for (int hj = 0; hj<hidden_dim_; hj++)
					  {

						  const int weight_h_index = hi*hidden_dim_ + hj;


						  cell_outputs_diff += weight_hhx[weight_h_index] * cell_outputs_diff_x1;
						  cell_outputs_diff += weight_hhy[weight_h_index] * cell_outputs_diff_y1;	//Equation 8.15
						  cell_outputs_diff += weight_hhx[weight_h_index + sub_weight_offset_h] * input_gate_diff_x1;
						  cell_outputs_diff += weight_hhy[weight_h_index + sub_weight_offset_h] * input_gate_diff_y1;
						  cell_outputs_diff += weight_hhx[weight_h_index + sub_weight_offset_h * 2] * output_gate_diff_x1;
						  cell_outputs_diff += weight_hhy[weight_h_index + sub_weight_offset_h * 2] * output_gate_diff_y1;
						  cell_outputs_diff += weight_hhx[weight_h_index + sub_weight_offset_h * 3] * forget_gate_diff_x1;
						  cell_outputs_diff += weight_hhy[weight_h_index + sub_weight_offset_h * 3] * forget_gate_diff_y1;	//Equation 8.15
					  }
					  output_gates_diff[output_index] = cell_outputs_diff*tanh(cell_states_map[output_index])*dsigmoid(output_gates_map[output_index]);	//Equation 8.16

					  cell_states_diff[output_index] = output_gates_map[output_index] * dtanh(top_data[output_index])*cell_outputs_diff;
					  cell_states_diff[output_index] += weight_cg[weight_c_index] * input_gate_diff_x1;
					  cell_states_diff[output_index] += weight_cg[weight_c_index + 1] * input_gate_diff_y1;

					  cell_states_diff[output_index] += weight_cg[weight_c_index + 2] * forget_gate_diff_x1;
					  cell_states_diff[output_index] += weight_cg[weight_c_index + 3] * forget_gate_diff_y1;
					  cell_states_diff[output_index] += weight_cg[weight_c_index + 4] * output_gate_diff;
					  cell_states_diff[output_index] += forget_gate_x1*cell_states_x1;
					  cell_states_diff[output_index] += forget_gate_y1*cell_states_y1;//Equation 8.17
					  cell_input_diff = input_gates_map[output_index] * dtanh(net_inputs_map[output_index])*cell_states_diff[output_index];	//Equation 8.18
					  forget_gates_diff[output_index] = dsigmoid(forget_gates_map[output_index])*cell_states_diff[output_index] * (cell_states_x_1 + cell_states_y_1);	//Equation 8.19
					  input_gates_diff[output_index] = dsigmoid(input_gates_map[output_index])*cell_states_diff[output_index] * net_inputs_map[output_index];	//Eqaaution 8.20

					  int hstart = oh * stride_height_;
					  int wstart = ow * stride_width_;
					  int hend = min(hstart + kernel_height_, input_height_);
					  int wend = min(wstart + kernel_width_, input_width_);
					  hstart = max(hstart, 0);
					  wstart = max(wstart, 0);
					 
					  int weight_offset = kernel_height_*kernel_width_*hi*channels_*weight_groups;
					  for (int c = 0; c < channels_; ++c)
					  {
						  int weight_index = 0;
						  for (int h = hstart; h < hend; ++h) {
							 
							  for (int w = wstart; w < wend; ++w) {
								  int index = h * input_width_ + c*input_height_*input_width_ + w;
								  dw_ih[weight_index + weight_offset] += bottom_data[index] * cell_input_diff;
								  dw_ih[weight_index + weight_offset + sub_weight_offset] += bottom_data[index] * input_gates_diff[output_index];
								  dw_ih[weight_index + weight_offset + sub_weight_offset * 2] += bottom_data[index] * output_gates_diff[output_index];
								  dw_ih[weight_index + weight_offset + sub_weight_offset * 3] += bottom_data[index] * forget_gates_diff[output_index];
								  bottom_diff[index] += weight_ih[weight_index + weight_offset] * cell_input_diff;
								  bottom_diff[index] += weight_ih[weight_index + weight_offset + sub_weight_offset] * input_gates_diff[output_index];
								  bottom_diff[index] += weight_ih[weight_index + weight_offset + sub_weight_offset * 2] * output_gates_diff[output_index];
								  bottom_diff[index] += weight_ih[weight_index + weight_offset + sub_weight_offset * 3] * forget_gates_diff[output_index];
								  weight_index++;
							  }
						  }
						  weight_offset += kernel_height_*kernel_width_*weight_groups;
					  }



					  for (int hj = 0; hj < hidden_dim_; hj++)
					  {
						  const int weight_h_index = hj*hidden_dim_ + hi;
						  dw_hhx[weight_h_index] += cell_input_diff*cell_outputs_x_1;
						  dw_hhy[weight_h_index] += cell_input_diff*cell_outputs_y_1;

						  dw_hhx[weight_h_index + sub_weight_offset_h] += input_gates_diff[output_index] * cell_outputs_x_1;
						  dw_hhy[weight_h_index + sub_weight_offset_h] += input_gates_diff[output_index] * cell_outputs_y_1;

						  dw_hhx[weight_h_index + sub_weight_offset_h * 2] += output_gates_diff[output_index] * cell_outputs_x_1;
						  dw_hhy[weight_h_index + sub_weight_offset_h * 2] += output_gates_diff[output_index] * cell_outputs_y_1;

						  dw_hhx[weight_h_index + sub_weight_offset_h * 3] += forget_gates_diff[output_index] * cell_outputs_x_1;
						  dw_hhy[weight_h_index + sub_weight_offset_h * 3] += forget_gates_diff[output_index] * cell_outputs_y_1;


					  }

					  dw_cg[hi * 5] += cell_states_x_1 * input_gates_diff[output_index];
					  dw_cg[hi * 5 + 1] += cell_states_y_1* input_gates_diff[output_index];
					  dw_cg[hi * 5 + 2] += cell_states_x_1 * forget_gates_diff[output_index];
					  dw_cg[hi * 5 + 3] += cell_states_y_1* forget_gates_diff[output_index];
					  dw_cg[hi * 5 + 4] += cell_states_map[output_index] * output_gates_diff[output_index];

				  }


			  }


		  }
		  top_data += top[0]->offset(1, 0);
		  top_diff += top[0]->offset(1, 0);
		  cell_states_map += top[0]->offset(1, 0);
		  input_gates_map += top[0]->offset(1, 0);
		  output_gates_map += top[0]->offset(1, 0);
		  forget_gates_map += top[0]->offset(1, 0);
		  net_inputs_map += top[0]->offset(1, 0);
		  cell_states_diff += top[0]->offset(1, 0);
		  input_gates_diff += top[0]->offset(1, 0);
		  output_gates_diff += top[0]->offset(1, 0);
		  forget_gates_diff += top[0]->offset(1, 0);
		  bottom_diff += bottom[0]->offset(1, 0);
		  bottom_data += bottom[0]->offset(1, 0);
	  }
	  break;
  case 3:	//bottom left
	  for (int n = 0; n < top[0]->num(); ++n) {
		  for (int oh = 0; oh <output_height_; ++oh) {
			  for (int ow = output_width_ - 1; ow >= 0; --ow){
				  for (int hi = 0; hi < hidden_dim_; hi++)	//hid=num_output
				  {
					  const int output_index = oh * output_width_ + ow + hi*output_height_*output_width_;
					  if (ow<output_width_ - 1)
						  cell_outputs_diff_x1 = top_diff[output_index + 1];
					  else
						  cell_outputs_diff_x1 = 0;
					  if (oh>0)
						  cell_outputs_diff_y1 = top_diff[output_index - output_width_];
					  else
						  cell_outputs_diff_y1 = 0;
					  if (ow<output_width_ - 1)
						  cell_states_diff_x1 = cell_states_diff[output_index + 1];
					  else
						  cell_states_diff_x1 = 0;
					  if (oh>0)
						  cell_states_diff_y1 = cell_states_diff[output_index - output_width_];
					  else
						  cell_states_diff_y1 = 0;
					  if (ow<output_width_ - 1)
						  input_gate_diff_x1 = input_gates_diff[output_index + 1];
					  else
						  input_gate_diff_x1 = 0;
					  if (oh>0)
						  input_gate_diff_y1 = input_gates_diff[output_index - output_width_];
					  else
						  input_gate_diff_y1 = 0;
					  if (ow>0)
						  output_gate_diff_x1 = output_gates_diff[output_index - 1];
					  else
						  output_gate_diff_x1 = 0;
					  if (oh<output_height_ - 1)
						  output_gate_diff_y1 = output_gates_diff[output_index + output_width_];
					  else
						  output_gate_diff_y1 = 0;
					  if (ow<output_width_ - 1)
						  forget_gate_diff_x1 = forget_gates_diff[output_index + 1];
					  else
						  forget_gate_diff_x1 = 0;
					  if (oh>0)
						  forget_gate_diff_y1 = forget_gates_diff[output_index - output_width_];
					  else
						  forget_gate_diff_y1 = 0;
					  if (ow<output_width_ - 1)
						  forget_gate_x1 = forget_gates_map[output_index + 1];
					  else
						  forget_gate_x1 = 0;
					  if (oh>0)
						  forget_gate_y1 = forget_gates_map[output_index - output_width_];
					  else
						  forget_gate_y1 = 0;

					  if (ow<output_width_ - 1)
						  cell_states_x1 = cell_states_map[output_index + 1];
					  else
						  cell_states_x1 = 0;
					  if (oh>0)
						  cell_states_y1 = cell_states_map[output_index - output_width_];
					  else
						  cell_states_y1 = 0;
					  if (ow>0)
						  cell_states_x_1 = cell_states_map[output_index - 1];
					  else
						  cell_states_x_1 = 0;
					  if (oh<output_height_ - 1)
						  cell_states_y_1 = cell_states_map[output_index + output_width_];
					  else
						  cell_states_y_1 = 0;
					  if (ow>0)
						  cell_outputs_x_1 = top_data[output_index - 1];
					  else
						  cell_outputs_x_1 = 0;
					  if (oh<output_height_ - 1)
						  cell_outputs_y_1 = top_data[output_index + output_width_];
					  else
						  cell_outputs_y_1 = 0;
					  cell_outputs_diff = top_diff[output_index];
					  //need adding hstart
					  const int sub_weight_offset = kernel_height_*kernel_width_;
					  const int sub_weight_offset_h = hidden_dim_*hidden_dim_;

					  const int weight_c_index = hi * 5;
					  for (int hj = 0; hj<hidden_dim_; hj++)
					  {

						  const int weight_h_index = hi*hidden_dim_ + hj;


						  cell_outputs_diff += weight_hhx[weight_h_index] * cell_outputs_diff_x1;
						  cell_outputs_diff += weight_hhy[weight_h_index] * cell_outputs_diff_y1;	//Equation 8.15
						  cell_outputs_diff += weight_hhx[weight_h_index + sub_weight_offset_h] * input_gate_diff_x1;
						  cell_outputs_diff += weight_hhy[weight_h_index + sub_weight_offset_h] * input_gate_diff_y1;
						  cell_outputs_diff += weight_hhx[weight_h_index + sub_weight_offset_h * 2] * output_gate_diff_x1;
						  cell_outputs_diff += weight_hhy[weight_h_index + sub_weight_offset_h * 2] * output_gate_diff_y1;
						  cell_outputs_diff += weight_hhx[weight_h_index + sub_weight_offset_h * 3] * forget_gate_diff_x1;
						  cell_outputs_diff += weight_hhy[weight_h_index + sub_weight_offset_h * 3] * forget_gate_diff_y1;	//Equation 8.15
					  }
					  output_gates_diff[output_index] = cell_outputs_diff*tanh(cell_states_map[output_index])*dsigmoid(output_gates_map[output_index]);	//Equation 8.16
					  cell_states_diff[output_index] = output_gates_map[output_index] * dtanh(top_data[output_index])*cell_outputs_diff;
					  cell_states_diff[output_index] += weight_cg[weight_c_index] * input_gate_diff_x1;
					  cell_states_diff[output_index] += weight_cg[weight_c_index + 1] * input_gate_diff_y1;

					  cell_states_diff[output_index] += weight_cg[weight_c_index + 2] * forget_gate_diff_x1;
					  cell_states_diff[output_index] += weight_cg[weight_c_index + 3] * forget_gate_diff_y1;
					  cell_states_diff[output_index] += weight_cg[weight_c_index + 4] * output_gate_diff;
					  cell_states_diff[output_index] += forget_gate_x1*cell_states_x1;
					  cell_states_diff[output_index] += forget_gate_y1*cell_states_y1;//Equation 8.17
					  cell_input_diff = input_gates_map[output_index] * dtanh(net_inputs_map[output_index])*cell_states_diff[output_index];	//Equation 8.18
					  forget_gates_diff[output_index] = dsigmoid(forget_gates_map[output_index])*cell_states_diff[output_index] * (cell_states_x_1 + cell_states_y_1);	//Equation 8.19
					  input_gates_diff[output_index] = dsigmoid(input_gates_map[output_index])*cell_states_diff[output_index] * net_inputs_map[output_index];	//Eqaaution 8.20

					  int hstart = oh * stride_height_;
					  int wstart = ow * stride_width_;
					  int hend = min(hstart + kernel_height_, input_height_);
					  int wend = min(wstart + kernel_width_, input_width_);
					  hstart = max(hstart, 0);
					  wstart = max(wstart, 0);
					  
					  int weight_offset = kernel_height_*kernel_width_*hi*channels_*weight_groups;
					  for (int c = 0; c < channels_; ++c)
					  {
						  int weight_index = 0;
						  for (int h = hstart; h < hend; ++h) {
							  for (int w = wstart; w < wend; ++w) {
								  int index = h * input_width_ + c*input_height_*input_width_ + w;
								  dw_ih[weight_index + weight_offset] += bottom_data[index] * cell_input_diff;
								  dw_ih[weight_index + weight_offset + sub_weight_offset] += bottom_data[index] * input_gates_diff[output_index];
								  dw_ih[weight_index + weight_offset + sub_weight_offset * 2] += bottom_data[index] * output_gates_diff[output_index];
								  dw_ih[weight_index + weight_offset + sub_weight_offset * 3] += bottom_data[index] * forget_gates_diff[output_index];
								  bottom_diff[index] += weight_ih[weight_index + weight_offset] * cell_input_diff;
								  bottom_diff[index] += weight_ih[weight_index + weight_offset + sub_weight_offset] * input_gates_diff[output_index];
								  bottom_diff[index] += weight_ih[weight_index + weight_offset + sub_weight_offset * 2] * output_gates_diff[output_index];
								  bottom_diff[index] += weight_ih[weight_index + weight_offset + sub_weight_offset * 3] * forget_gates_diff[output_index];
								  weight_index++;
							  }
						  }
						  weight_offset += kernel_height_*kernel_width_*weight_groups;
					  }



					  for (int hj = 0; hj < hidden_dim_; hj++)
					  {
						  const int weight_h_index = hj*hidden_dim_ + hi;
						  dw_hhx[weight_h_index] += cell_input_diff*cell_outputs_x_1;
						  dw_hhy[weight_h_index] += cell_input_diff*cell_outputs_y_1;

						  dw_hhx[weight_h_index + sub_weight_offset_h] += input_gates_diff[output_index] * cell_outputs_x_1;
						  dw_hhy[weight_h_index + sub_weight_offset_h] += input_gates_diff[output_index] * cell_outputs_y_1;

						  dw_hhx[weight_h_index + sub_weight_offset_h * 2] += output_gates_diff[output_index] * cell_outputs_x_1;
						  dw_hhy[weight_h_index + sub_weight_offset_h * 2] += output_gates_diff[output_index] * cell_outputs_y_1;

						  dw_hhx[weight_h_index + sub_weight_offset_h * 3] += forget_gates_diff[output_index] * cell_outputs_x_1;
						  dw_hhy[weight_h_index + sub_weight_offset_h * 3] += forget_gates_diff[output_index] * cell_outputs_y_1;


					  }
					  dw_cg[hi * 5] += cell_states_x_1 * input_gates_diff[output_index];
					  dw_cg[hi * 5 + 1] += cell_states_y_1* input_gates_diff[output_index];
					  dw_cg[hi * 5 + 2] += cell_states_x_1 * forget_gates_diff[output_index];
					  dw_cg[hi * 5 + 3] += cell_states_y_1* forget_gates_diff[output_index];
					  dw_cg[hi * 5 + 4] += cell_states_map[output_index] * output_gates_diff[output_index];

				  }


			  }


		  }
		  top_data += top[0]->offset(1, 0);
		  top_diff += top[0]->offset(1, 0);
		  cell_states_map += top[0]->offset(1, 0);
		  input_gates_map += top[0]->offset(1, 0);
		  output_gates_map += top[0]->offset(1, 0);
		  forget_gates_map += top[0]->offset(1, 0);
		  net_inputs_map += top[0]->offset(1, 0);
		  cell_states_diff += top[0]->offset(1, 0);
		  input_gates_diff += top[0]->offset(1, 0);
		  output_gates_diff += top[0]->offset(1, 0);
		  forget_gates_diff += top[0]->offset(1, 0);
		  bottom_diff += bottom[0]->offset(1, 0);
		  bottom_data += bottom[0]->offset(1, 0);
	  }
	  break;
  case 4:	//bottom right
	  FILE* fp1;
	  for (int n = 0; n < top[0]->num(); ++n) {
		  tempchar[0] = '\0';
		  sprintf(tempchar, "top_diff%d.txt", n);
		  fopen_s(&fp1, tempchar, "w");
		  int tempcount = 0;
		  for (int i = 0; i < output_height_; i++)
		  {
			  for (int j = 0; j < output_width_; j++)
			  {
				  fprintf(fp1, "%f\t", top_diff[tempcount]);
				  tempcount++;
			  }
			  fprintf(fp1, "\n");
		  }
		  fclose(fp1);
		  for (int oh = 0; oh <output_height_; ++oh) {
			  for (int ow = 0; ow <output_width_; ++ow){
				  for (int hi = 0; hi < hidden_dim_; hi++)	//hid=num_output
				  {
					  const int output_index = oh * output_width_ + ow + hi*output_height_*output_width_ ;
					  if (ow>0)
						  cell_outputs_diff_x1 = top_diff[output_index - 1];
					  else
						  cell_outputs_diff_x1 = 0;
					  if (oh>0)
						  cell_outputs_diff_y1 = top_diff[output_index - output_width_];
					  else
						  cell_outputs_diff_y1 = 0;
					  if (ow>0)
						  cell_states_diff_x1 = cell_states_diff[output_index - 1];
					  else
						  cell_states_diff_x1 = 0;
					  if (oh>0)
						  cell_states_diff_y1 = cell_states_diff[output_index - output_width_];
					  else
						  cell_states_diff_y1 = 0;
					  if (ow>0)
						  input_gate_diff_x1 = input_gates_diff[output_index - 1];
					  else
						  input_gate_diff_x1 = 0;
					  if (oh>0)
						  input_gate_diff_y1 = input_gates_diff[output_index - output_width_];
					  else
						  input_gate_diff_y1 = 0;
					  if (ow>0)
						  output_gate_diff_x1 = output_gates_diff[output_index - 1];
					  else
						  output_gate_diff_x1 = 0;
					  if (oh<output_height_ - 1)
						  output_gate_diff_y1 = output_gates_diff[output_index + output_width_];
					  else
						  output_gate_diff_y1 = 0;
					  if (ow>0)
						  forget_gate_diff_x1 = forget_gates_diff[output_index - 1];
					  else
						  forget_gate_diff_x1 = 0;
					  if (oh>0)
						  forget_gate_diff_y1 = forget_gates_diff[output_index - output_width_];
					  else
						  forget_gate_diff_y1 = 0;
					  if (ow>0)
						  forget_gate_x1 = forget_gates_map[output_index - 1];
					  else
						  forget_gate_x1 = 0;
					  if (oh>0)
						  forget_gate_y1 = forget_gates_map[output_index - output_width_];
					  else
						  forget_gate_y1 = 0;

					  if (ow>0)
						  cell_states_x1 = cell_states_map[output_index - 1];
					  else
						  cell_states_x1 = 0;
					  if (oh>0)
						  cell_states_y1 = cell_states_map[output_index - output_width_];
					  else
						  cell_states_y1 = 0;
					  if (ow < output_width_ - 1)
						  cell_states_x_1 = cell_states_map[output_index + 1];
					  else
						  cell_states_x_1 = 0;
					  if (oh<output_height_ - 1)
						  cell_states_y_1 = cell_states_map[output_index + output_width_];
					  else
						  cell_states_y_1 = 0;
					  if (ow<output_width_ - 1)
						  cell_outputs_x_1 = top_data[output_index + 1];
					  else
						  cell_outputs_x_1 = 0;
					  if (oh<output_height_ - 1)
						  cell_outputs_y_1 = top_data[output_index + output_width_];
					  else
						  cell_outputs_y_1 = 0;
					  cell_outputs_diff = top_diff[output_index];
					  if (abs(cell_outputs_diff)>0.1)
						  int tempint0 = 0;
					  //need adding hstart
					  const int sub_weight_offset = kernel_height_*kernel_width_;
					  const int sub_weight_offset_h = hidden_dim_*hidden_dim_;

					  const int weight_c_index = hi * 5;
					  for (int hj = 0; hj<hidden_dim_; hj++)
					  {

						  const int weight_h_index = hi*hidden_dim_ + hj;


						  cell_outputs_diff += weight_hhx[weight_h_index] * cell_outputs_diff_x1;
						  cell_outputs_diff += weight_hhy[weight_h_index] * cell_outputs_diff_y1;	//Equation 8.15
						  cell_outputs_diff += weight_hhx[weight_h_index + sub_weight_offset_h] * input_gate_diff_x1;
						  cell_outputs_diff += weight_hhy[weight_h_index + sub_weight_offset_h] * input_gate_diff_y1;
						  cell_outputs_diff += weight_hhx[weight_h_index + sub_weight_offset_h * 2] * output_gate_diff_x1;
						  cell_outputs_diff += weight_hhy[weight_h_index + sub_weight_offset_h * 2] * output_gate_diff_y1;
						  cell_outputs_diff += weight_hhx[weight_h_index + sub_weight_offset_h * 3] * forget_gate_diff_x1;
						  cell_outputs_diff += weight_hhy[weight_h_index + sub_weight_offset_h * 3] * forget_gate_diff_y1;	//Equation 8.15
						  if (cell_outputs_diff>0.0001)
							  int tempint0 = 0;
					  }
					  output_gates_diff[output_index] = cell_outputs_diff*tanh(cell_states_map[output_index])*dsigmoid(output_gates_map[output_index]);	//Equation 8.16

					  cell_states_diff[output_index] = output_gates_map[output_index] * dtanh(top_data[output_index])*cell_outputs_diff;
					  cell_states_diff[output_index] += weight_cg[weight_c_index] * input_gate_diff_x1;
					  cell_states_diff[output_index] += weight_cg[weight_c_index + 1] * input_gate_diff_y1;
					  cell_states_diff[output_index] += weight_cg[weight_c_index + 2] * forget_gate_diff_x1;
					  cell_states_diff[output_index] += weight_cg[weight_c_index + 3] * forget_gate_diff_y1;
					  cell_states_diff[output_index] += weight_cg[weight_c_index + 4] * output_gate_diff;
					  cell_states_diff[output_index] += forget_gate_x1*cell_states_x1;
					  cell_states_diff[output_index] += forget_gate_y1*cell_states_y1;//Equation 8.17
					  if (cell_outputs_diff>0.0001)
						  int tempint0 = 0;
					  cell_input_diff = input_gates_map[output_index] * dtanh(net_inputs_map[output_index])*cell_states_diff[output_index];	//Equation 8.18
					  if (cell_input_diff > 100)
					  {
						  float tempfloat = input_gates_map[output_index];
						  tempfloat = net_inputs_map[output_index];
						  tempfloat = cell_states_diff[output_index];
					  }
					  forget_gates_diff[output_index] = dsigmoid(forget_gates_map[output_index])*cell_states_diff[output_index] * (cell_states_x_1 + cell_states_y_1);	//Equation 8.19
					  if (forget_gates_diff[output_index]>100)
						  int tempint0 = 0;
					  input_gates_diff[output_index] = dsigmoid(input_gates_map[output_index])*cell_states_diff[output_index] * net_inputs_map[output_index];	//Eqaaution 8.20

					  int hstart = oh * stride_height_;
					  int wstart = ow * stride_width_;
					  int hend = min(hstart + kernel_height_, input_height_);
					  int wend = min(wstart + kernel_width_, input_width_);
					  hstart = max(hstart, 0);
					  wstart = max(wstart, 0);
					  
					  int weight_offset = kernel_height_*kernel_width_*hi*channels_*weight_groups;
					  for (int c = 0; c < channels_; ++c)
					  {
						  int weight_index = 0;
						  for (int h = hstart; h < hend; ++h) {
							  for (int w = wstart; w < wend; ++w) {
								  int index = h * input_width_ + c*input_height_*input_width_ + w;
								  dw_ih[weight_index + weight_offset] += bottom_data[index] * cell_input_diff;
								  dw_ih[weight_index + weight_offset + sub_weight_offset] += bottom_data[index] * input_gates_diff[output_index];
								  dw_ih[weight_index + weight_offset + sub_weight_offset * 2] += bottom_data[index] * output_gates_diff[output_index];
								  dw_ih[weight_index + weight_offset + sub_weight_offset * 3] += bottom_data[index] * forget_gates_diff[output_index];
								  bottom_diff[index] += weight_ih[weight_index + weight_offset] * cell_input_diff;
								  bottom_diff[index] += weight_ih[weight_index + weight_offset + sub_weight_offset] * input_gates_diff[output_index];
								  bottom_diff[index] += weight_ih[weight_index + weight_offset + sub_weight_offset * 2] * output_gates_diff[output_index];
								  bottom_diff[index] += weight_ih[weight_index + weight_offset + sub_weight_offset * 3] * forget_gates_diff[output_index];
								  weight_index++;
							  }
						  }
						  weight_offset += kernel_height_*kernel_width_*weight_groups;
					  }



					  for (int hj = 0; hj < hidden_dim_; hj++)
					  {
						  const int weight_h_index = hj*hidden_dim_ + hi;
						  dw_hhx[weight_h_index] += cell_input_diff*cell_outputs_x_1;
						  dw_hhy[weight_h_index] += cell_input_diff*cell_outputs_y_1;

						  dw_hhx[weight_h_index + sub_weight_offset_h] += input_gates_diff[output_index] * cell_outputs_x_1;
						  dw_hhy[weight_h_index + sub_weight_offset_h] += input_gates_diff[output_index] * cell_outputs_y_1;

						  dw_hhx[weight_h_index + sub_weight_offset_h * 2] += output_gates_diff[output_index] * cell_outputs_x_1;
						  dw_hhy[weight_h_index + sub_weight_offset_h * 2] += output_gates_diff[output_index] * cell_outputs_y_1;

						  dw_hhx[weight_h_index + sub_weight_offset_h * 3] += forget_gates_diff[output_index] * cell_outputs_x_1;
						  dw_hhy[weight_h_index + sub_weight_offset_h * 3] += forget_gates_diff[output_index] * cell_outputs_y_1;


					  }

					  dw_cg[hi * 5] += cell_states_x_1 * input_gates_diff[output_index];
					  dw_cg[hi * 5 + 1] += cell_states_y_1* input_gates_diff[output_index];
					  dw_cg[hi * 5 + 2] += cell_states_x_1 * forget_gates_diff[output_index];
					  dw_cg[hi * 5 + 3] += cell_states_y_1* forget_gates_diff[output_index];
					  dw_cg[hi * 5 + 4] += cell_states_map[output_index] * output_gates_diff[output_index];

				  }


			  }


		  }
		  top_data += top[0]->offset(1, 0);
		  top_diff += top[0]->offset(1, 0);
		  cell_states_map += top[0]->offset(1, 0);
		  input_gates_map += top[0]->offset(1, 0);
		  output_gates_map += top[0]->offset(1, 0);
		  forget_gates_map += top[0]->offset(1, 0);
		  net_inputs_map += top[0]->offset(1, 0);
		  cell_states_diff += top[0]->offset(1, 0);
		  input_gates_diff += top[0]->offset(1, 0);
		  output_gates_diff += top[0]->offset(1, 0);
		  forget_gates_diff += top[0]->offset(1, 0);
		  bottom_diff += bottom[0]->offset(1, 0);
		  bottom_data += bottom[0]->offset(1, 0);
	  }
	 
	  
	  break;

  }

  top_data -= top[0]->offset(top[0]->num(), 0);
  bottom_data -= bottom[0]->offset(bottom[0]->num(), 0);
  top_diff -= top[0]->offset(top[0]->num(), 0);
  cell_states_map -= top[0]->offset(top[0]->num(), 0);
  input_gates_map -= top[0]->offset(top[0]->num(), 0);
  output_gates_map -= top[0]->offset(top[0]->num(), 0);
  forget_gates_map -= top[0]->offset(top[0]->num(), 0);
  net_inputs_map -= top[0]->offset(top[0]->num(), 0);
  cell_states_diff -= top[0]->offset(top[0]->num(), 0);
  input_gates_diff -= top[0]->offset(top[0]->num(), 0);
  output_gates_diff -= top[0]->offset(top[0]->num(), 0);
  forget_gates_diff -= top[0]->offset(top[0]->num(), 0);
  bottom_diff -= bottom[0]->offset(bottom[0]->num(), 0);
  int weight_index = 0;
  const int output_size = output_width_*output_height_*top[0]->num();
  const int sub_weight_offset = kernel_height_*kernel_width_;
  const int sub_weight_offset_h = hidden_dim_*hidden_dim_;
  for (int hi = 0; hi < hidden_dim_; hi++)
  {
	  int weight_offset = channels_*kernel_height_*kernel_width_*hi*weight_groups;
	  for (int c = 0; c < channels_; ++c)
	  {
		  weight_index = 0;
		  for (int h = 0; h < kernel_height_; ++h) {
			  for (int w = 0; w < kernel_width_; ++w) {
				  dw_ih[weight_index + weight_offset] /= output_size;
				  dw_ih[weight_index + weight_offset + sub_weight_offset] /= output_size;
				  dw_ih[weight_index + weight_offset + sub_weight_offset * 2] /= output_size;
				  dw_ih[weight_index + weight_offset + sub_weight_offset * 3] /= output_size;
				  weight_index++;
			  }
		  }
		  weight_offset += kernel_height_*kernel_width_*weight_groups;
	  }
	 
  }

  for (int hi = 0; hi < hidden_dim_; hi++)
  {
	  for (int hj = 0; hj<hidden_dim_; hj++)
	  {
		  const int weight_h_index = hi*hidden_dim_ + hj;
		  dw_hhx[weight_h_index] /= output_size;
		  dw_hhx[weight_h_index + sub_weight_offset_h] /= output_size;
		  dw_hhx[weight_h_index + sub_weight_offset_h * 2] /= output_size;
		  dw_hhx[weight_h_index + sub_weight_offset_h * 3] /= output_size;
		  dw_hhy[weight_h_index] /= output_size;
		  dw_hhy[weight_h_index + sub_weight_offset_h] /= output_size;
		  dw_hhy[weight_h_index + sub_weight_offset_h * 2] /= output_size;
		  dw_hhy[weight_h_index + sub_weight_offset_h * 3] /= output_size;
	  }
  }
  for (int hi = 0; hi < hidden_dim_; hi++)
  {
	  for (int hj = 0; hj<5; hj++)
	  {
		  const int weight_h_index = hi*hidden_dim_ + hj;
		  dw_cg[weight_h_index] /= output_size;
	  }
  }
  //FILE* fp;
  //fopen_s(&fp, "weight_ih.txt", "w");

  //for (int hi = 0; hi < hidden_dim_; hi++)
  //{
	 // int weight_offset = channels_*kernel_height_*kernel_width_*hi*weight_groups;
	 // for (int c = 0; c < channels_; ++c)
	 // {
		//  weight_index = 0;
		//  for (int h = 0; h < kernel_height_; ++h) {
		//	  for (int w = 0; w < kernel_width_; ++w) {
		//		  fprintf(fp, "%f\t", weight_ih[weight_index + weight_offset]);
		//		  weight_index++;
		//	  }
		//	  fprintf(fp, "\n");
		//  }
		//  weight_offset += kernel_height_*kernel_width_*weight_groups;
	 // }
	 // fprintf(fp, "\n");
	 // weight_offset = channels_*kernel_height_*kernel_width_*hi*weight_groups;
	 // for (int c = 0; c < channels_; ++c)
	 // {
		//  weight_index = 0;
		//  for (int h = 0; h < kernel_height_; ++h) {
		//	  for (int w = 0; w < kernel_width_; ++w) {
		//		  fprintf(fp, "%f\t", weight_ih[weight_index + weight_offset + sub_weight_offset]);
		//		  weight_index++;
		//	  }
		//	  fprintf(fp, "\n");
		//  }
		//  weight_offset += kernel_height_*kernel_width_*weight_groups;
	 // }
	 // fprintf(fp, "\n");
	 // weight_offset = channels_*kernel_height_*kernel_width_*hi*weight_groups;
	 // for (int c = 0; c < channels_; ++c)
	 // {
		//  weight_index = 0;
		//  for (int h = 0; h < kernel_height_; ++h) {
		//	  int index = h * kernel_width_;
		//	  for (int w = 0; w < kernel_width_; ++w) {
		//		  index += w;
		//		  fprintf(fp, "%f\t", weight_ih[weight_index + weight_offset + sub_weight_offset * 2]);
		//		  weight_index++;
		//	  }
		//	  fprintf(fp, "\n");
		//  }
		//  weight_offset += kernel_height_*kernel_width_*weight_groups;
	 // }
	 // fprintf(fp, "\n");
	 // weight_offset = channels_*kernel_height_*kernel_width_*hi*weight_groups;
	 // for (int c = 0; c < channels_; ++c)
	 // {
		//  weight_index = 0;
		//  for (int h = 0; h < kernel_height_; ++h) {
		//	  for (int w = 0; w < kernel_width_; ++w) {
		//		  fprintf(fp, "%f\t", weight_ih[weight_index + weight_offset + sub_weight_offset * 3]);
		//		  weight_index++;
		//	  }
		//	  fprintf(fp, "\n");
		//  }
		//  weight_offset += kernel_height_*kernel_width_*weight_groups;
	 // }
  //}

  //fclose(fp);
  //fopen_s(&fp, "weight_hhx.txt", "w");

  //for (int hi = 0; hi < hidden_dim_; hi++)
  //{
	 // for (int hj = 0; hj<hidden_dim_; hj++)
	 // {
		//  const int weight_h_index = hi*hidden_dim_ + hj;
		//  fprintf(fp, "%f\t", weight_hhx[weight_h_index]);
	 // }
	 // fprintf(fp, "\n");
  //}
  //for (int hi = 0; hi < hidden_dim_; hi++)
  //{
	 // for (int hj = 0; hj<hidden_dim_; hj++)
	 // {
		//  const int weight_h_index = hi*hidden_dim_ + hj;
		//  fprintf(fp, "%f\t", weight_hhx[weight_h_index + sub_weight_offset_h]);
	 // }
	 // fprintf(fp, "\n");
  //}
  //for (int hi = 0; hi < hidden_dim_; hi++)
  //{
	 // for (int hj = 0; hj<hidden_dim_; hj++)
	 // {
		//  const int weight_h_index = hi*hidden_dim_ + hj;
		//  fprintf(fp, "%f\t", weight_hhx[weight_h_index + sub_weight_offset_h * 2]);
	 // }
	 // fprintf(fp, "\n");
  //}
  //for (int hi = 0; hi < hidden_dim_; hi++)
  //{
	 // for (int hj = 0; hj<hidden_dim_; hj++)
	 // {
		//  const int weight_h_index = hi*hidden_dim_ + hj;
		//  fprintf(fp, "%f\t", weight_hhx[weight_h_index + sub_weight_offset_h * 3]);
	 // }
	 // fprintf(fp, "\n");
  //}
  //fclose(fp);
  //fopen_s(&fp, "weight_hhy.txt", "w");
  //for (int hi = 0; hi < hidden_dim_; hi++)
  //{
	 // for (int hj = 0; hj<hidden_dim_; hj++)
	 // {
		//  const int weight_h_index = hi*hidden_dim_ + hj;
		//  fprintf(fp, "%f\t", weight_hhy[weight_h_index]);
	 // }
	 // fprintf(fp, "\n");
  //}
  //for (int hi = 0; hi < hidden_dim_; hi++)
  //{
	 // for (int hj = 0; hj<hidden_dim_; hj++)
	 // {
		//  const int weight_h_index = hi*hidden_dim_ + hj;
		//  fprintf(fp, "%f\t", weight_hhy[weight_h_index + sub_weight_offset_h]);
	 // }
	 // fprintf(fp, "\n");
  //}
  //for (int hi = 0; hi < hidden_dim_; hi++)
  //{
	 // for (int hj = 0; hj<hidden_dim_; hj++)
	 // {
		//  const int weight_h_index = hi*hidden_dim_ + hj;
		//  fprintf(fp, "%f\t", weight_hhy[weight_h_index + sub_weight_offset_h * 2]);
	 // }
	 // fprintf(fp, "\n");
  //}
  //for (int hi = 0; hi < hidden_dim_; hi++)
  //{
	 // for (int hj = 0; hj<hidden_dim_; hj++)
	 // {
		//  const int weight_h_index = hi*hidden_dim_ + hj;
		//  fprintf(fp, "%f\t", weight_hhy[weight_h_index + sub_weight_offset_h * 3]);
	 // }
	 // fprintf(fp, "\n");
  //}

  //fclose(fp);
  //fopen_s(&fp, "weight_cg.txt", "w");
  //for (int hi = 0; hi < hidden_dim_; hi++)
  //{
	 // for (int hj = 0; hj<5; hj++)
	 // {
		//  const int weight_h_index = hi*hidden_dim_ + hj;
		//  fprintf(fp, "%f\t", weight_cg[weight_h_index]);
	 // }
	 // fprintf(fp, "\n");
  //}
  //fclose(fp);

  //for (int n = 0; n < bottom[0]->num(); n++)
  //{
	 // tempchar[0] = '\0';
	 // sprintf(tempchar, "cell_states_map%d.txt", n);
	 // fopen_s(&fp, tempchar, "w");
	 // for (int h = 0; h < hidden_dim_; h++)
	 // for (int i = 0; i < output_height_; i++)
	 // {
		//  for (int j = 0; j < output_width_; j++)
		//  {
		//	  fprintf(fp, "%f\t", *cell_states_map);
		//	  cell_states_map++;
		//  }
		//  fprintf(fp, "\n");
	 // }
	 // fclose(fp);
	 // tempchar[0] = '\0';
	 // sprintf(tempchar, "input_gates_map%d.txt", n);
	 // fopen_s(&fp, tempchar, "w");
	 // for (int h = 0; h < hidden_dim_; h++)
	 // for (int i = 0; i < output_height_; i++)
	 // {
		//  for (int j = 0; j < output_width_; j++)
		//  {
		//	  fprintf(fp, "%f\t", *input_gates_map);
		//	  input_gates_map++;
		//  }
		//  fprintf(fp, "\n");
	 // }
	 // fclose(fp);
	 // tempchar[0] = '\0';
	 // sprintf(tempchar, "output_gates_map%d.txt", n);
	 // fopen_s(&fp, tempchar, "w");
	 // for (int h = 0; h < hidden_dim_; h++)
	 // for (int i = 0; i < output_height_; i++)
	 // {
		//  for (int j = 0; j < output_width_; j++)
		//  {
		//	  fprintf(fp, "%f\t", *output_gates_map);
		//	  output_gates_map++;
		//  }
		//  fprintf(fp, "\n");
	 // }
	 // fclose(fp);
	 // tempchar[0] = '\0';
	 // sprintf(tempchar, "forget_gates_map%d.txt", n);
	 // fopen_s(&fp, tempchar, "w");
	 // for (int h = 0; h < hidden_dim_; h++)
	 // for (int i = 0; i < output_height_; i++)
	 // {
		//  for (int j = 0; j < output_width_; j++)
		//  {
		//	  fprintf(fp, "%f\t", *forget_gates_map);
		//	  forget_gates_map++;
		//  }
		//  fprintf(fp, "\n");
	 // }
	 // fclose(fp);
	 // tempchar[0] = '\0';
	 // sprintf(tempchar, "cell_states_diff%d.txt", n);
	 // fopen_s(&fp, tempchar, "w");
	 // for (int h = 0; h < hidden_dim_; h++)
	 // for (int i = 0; i < output_height_; i++)
	 // {
		//  for (int j = 0; j < output_width_; j++)
		//  {
		//	  fprintf(fp, "%f\t", *cell_states_diff);
		//	  cell_states_diff++;
		//  }
		//  fprintf(fp, "\n");
	 // }
	 // fclose(fp);
	 // tempchar[0] = '\0';
	 // sprintf(tempchar, "input_gates_diff%d.txt", n);
	 // fopen_s(&fp, tempchar, "w");
	 // for (int h = 0; h < hidden_dim_; h++)
	 // for (int i = 0; i < output_height_; i++)
	 // {
		//  for (int j = 0; j < output_width_; j++)
		//  {
		//	  fprintf(fp, "%f\t", *input_gates_diff);
		//	  input_gates_diff++;
		//  }
		//  fprintf(fp, "\n");
	 // }
	 // fclose(fp);
	 // tempchar[0] = '\0';
	 // sprintf(tempchar, "output_gates_diff%d.txt", n);
	 // fopen_s(&fp, tempchar, "w");
	 // for (int h = 0; h < hidden_dim_; h++)
	 // for (int i = 0; i < output_height_; i++)
	 // {
		//  for (int j = 0; j < output_width_; j++)
		//  {
		//	  fprintf(fp, "%f\t", *output_gates_diff);
		//	  output_gates_diff++;
		//  }
		//  fprintf(fp, "\n");
	 // }
	 // fclose(fp);
	 // tempchar[0] = '\0';
	 // sprintf(tempchar, "forget_gates_diff%d.txt", n);
	 // fopen_s(&fp, tempchar, "w");
	 // for (int h = 0; h < hidden_dim_; h++)
	 // for (int i = 0; i < output_height_; i++)
	 // {
		//  for (int j = 0; j < output_width_; j++)
		//  {
		//	  fprintf(fp, "%f\t", *forget_gates_diff);
		//	  forget_gates_diff++;
		//  }
		//  fprintf(fp, "\n");
	 // }
	 // fclose(fp);
	 // tempchar[0] = '\0';
	 // sprintf(tempchar, "top_diff%d.txt", n);
	 // fopen_s(&fp, tempchar, "w");
	 // for (int h = 0; h < hidden_dim_; h++)
	 // for (int i = 0; i < output_height_; i++)
	 // {
		//  for (int j = 0; j < output_width_; j++)
		//  {
		//	  fprintf(fp, "%f\t", *top_diff);
		//	  top_diff++;
		//  }
		//  fprintf(fp, "\n");
	 // }
	 // fclose(fp);
	 // tempchar[0] = '\0';
	 // sprintf(tempchar, "top_data%d.txt", n);
	 // fopen_s(&fp, tempchar, "w");
	 // for (int h = 0; h < hidden_dim_; h++)
	 // {
		//  for (int i = 0; i < output_height_; i++)
		//  {
		//	  for (int j = 0; j < output_width_; j++)
		//	  {
		//		  fprintf(fp, "%f\t", *top_data);
		//		  top_data++;
		//	  }
		//	  fprintf(fp, "\n");
		//  }
	 // }
	 // fclose(fp);
	 // tempchar[0] = '\0';
	 // sprintf(tempchar, "bottom_data%d.txt", n);
	 // fopen_s(&fp, tempchar, "w");
	 // for (int c = 0; c < channels_; c++)
	 // {
		//  for (int i = 0; i < input_height_; i++)
		//  {
		//	  for (int j = 0; j < input_width_; j++)
		//	  {
		//		  fprintf(fp, "%f\t", *bottom_data);
		//		  bottom_data++;
		//	  }
		//	  fprintf(fp, "\n");
		//  }
	 // }
	 // fclose(fp);
	 // tempchar[0] = '\0';
	 // sprintf(tempchar, "net_inputs_map%d.txt", n);
	 // fopen_s(&fp, tempchar, "w");
	 // for (int h = 0; h < hidden_dim_;h++)
	 // for (int i = 0; i < output_height_; i++)
	 // {
		//  for (int j = 0; j < output_width_; j++)
		//  {
		//	  fprintf(fp, "%f\t", *net_inputs_map);
		//	  net_inputs_map++;
		//  }
		//  fprintf(fp, "\n");
	 // }
	 // fclose(fp);
	 // 
  //}
  top_data -= top[0]->offset(top[0]->num(), 0);
  bottom_data -= bottom[0]->offset(bottom[0]->num(), 0);
  top_diff -= top[0]->offset(top[0]->num(), 0);
  cell_states_map -= top[0]->offset(top[0]->num(), 0);
  input_gates_map -= top[0]->offset(top[0]->num(), 0);
  output_gates_map -= top[0]->offset(top[0]->num(), 0);
  forget_gates_map -= top[0]->offset(top[0]->num(), 0);
  net_inputs_map -= top[0]->offset(top[0]->num(), 0);
  cell_states_diff -= top[0]->offset(top[0]->num(), 0);
  input_gates_diff -= top[0]->offset(top[0]->num(), 0);
  output_gates_diff -= top[0]->offset(top[0]->num(), 0);
  forget_gates_diff -= top[0]->offset(top[0]->num(), 0);
  bottom_diff -= bottom[0]->offset(bottom[0]->num(), 0);
  //bottom_data -= bottom[0]->offset(bottom[0]->num(), 0);
  //top_data -= top[0]->offset(top[0]->num(), 0);
  //const int num = bottom[0]->shape(1);
  //const int x_dim = hidden_dim_ * 4;
  //const Dtype* C_prev = bottom[0]->cpu_data();
  //const Dtype* X = bottom[1]->cpu_data();
  //const Dtype* cont = bottom[2]->cpu_data();
  //const Dtype* C = top[0]->cpu_data();
  //const Dtype* H = top[1]->cpu_data();
  //const Dtype* C_diff = top[0]->cpu_diff();
  //const Dtype* H_diff = top[1]->cpu_diff();
  //Dtype* C_prev_diff = bottom[0]->mutable_cpu_diff();
  //Dtype* X_diff = bottom[1]->mutable_cpu_diff();
  //for (int n = 0; n < num; ++n) {
  //  for (int d = 0; d < hidden_dim_; ++d) {
  //    const Dtype i = sigmoid(X[d]);
  //    const Dtype f = (*cont == 0) ? 0 :
  //        (*cont * sigmoid(X[1 * hidden_dim_ + d]));
  //    const Dtype o = sigmoid(X[2 * hidden_dim_ + d]);
  //    const Dtype g = tanh(X[3 * hidden_dim_ + d]);
  //    const Dtype c_prev = C_prev[d];
  //    const Dtype c = C[d];
  //    const Dtype tanh_c = tanh(c);
  //    Dtype* c_prev_diff = C_prev_diff + d;
  //    Dtype* i_diff = X_diff + d;
  //    Dtype* f_diff = X_diff + 1 * hidden_dim_ + d;
  //    Dtype* o_diff = X_diff + 2 * hidden_dim_ + d;
  //    Dtype* g_diff = X_diff + 3 * hidden_dim_ + d;
  //    const Dtype c_term_diff =
  //        C_diff[d] + H_diff[d] * o * (1 - tanh_c * tanh_c);
  //    *c_prev_diff = c_term_diff * f;
  //    *i_diff = c_term_diff * g * i * (1 - i);
  //    *f_diff = c_term_diff * c_prev * f * (1 - f);
  //    *o_diff = H_diff[d] * tanh_c * o * (1 - o);
  //    *g_diff = c_term_diff * i * (1 - g * g);
  //  }
  //  C_prev += hidden_dim_;
  //  X += x_dim;
  //  C += hidden_dim_;
  //  H += hidden_dim_;
  //  C_diff += hidden_dim_;
  //  H_diff += hidden_dim_;
  //  X_diff += x_dim;
  //  C_prev_diff += hidden_dim_;
  //  ++cont;
  //}
}

#ifdef CPU_ONLY
STUB_GPU(LSTMUnitLayer);
#endif

INSTANTIATE_CLASS(LSTMUnitLayer);
REGISTER_LAYER_CLASS(LSTMUnit);

}  // namespace caffe
