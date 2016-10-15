package com.example.takephotodemo;

import java.io.BufferedReader;
import java.io.File;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;
import java.util.Set;
import org.apache.http.HttpEntity;
import org.apache.http.HttpResponse;
import org.apache.http.HttpStatus;
import org.apache.http.StatusLine;
import org.apache.http.client.HttpClient;
import org.apache.http.client.entity.UrlEncodedFormEntity;
import org.apache.http.client.methods.HttpGet;
import org.apache.http.client.methods.HttpPost;
import org.apache.http.entity.mime.MultipartEntity;
import org.apache.http.entity.mime.content.FileBody;
import org.apache.http.entity.mime.content.StringBody;
import org.apache.http.impl.client.DefaultHttpClient;
import org.apache.http.message.BasicNameValuePair;

public class NetUtil {
	/**
	 * 以POST方式提交表单
	 * 
	 * @param url
	 *            服务器路径
	 * @param param
	 *            参数键值对
	 * @return 响应结果
	 * @throws Exception
	 */
	public static String doPost(String url, Map<String, Object> param)
			throws Exception {
		HttpClient client = new DefaultHttpClient();
		HttpPost post = new HttpPost(url);
		if (param != null && param.size() > 0) {
			List<BasicNameValuePair> nameValuePairs = new ArrayList<BasicNameValuePair>(
					param.size());
			Set<String> keys = param.keySet();
			for (Object o : keys) {
				String key = (String) o;
				nameValuePairs.add(new BasicNameValuePair(key, String
						.valueOf(param.get(key))));
			}
			post.setEntity(new UrlEncodedFormEntity(nameValuePairs, "utf-8"));
		}
		HttpResponse response = client.execute(post);
		/** 返回状态 **/
		int statusCode = response.getStatusLine().getStatusCode();
		StringBuffer sb = new StringBuffer();
		if (statusCode == HttpStatus.SC_OK) {
			HttpEntity entity = response.getEntity();
			if (entity != null) {
				InputStream instream = entity.getContent();
				BufferedReader br = new BufferedReader(new InputStreamReader(
						instream));
				String tempLine;
				while ((tempLine = br.readLine()) != null) {
					sb.append(tempLine);
				}
			}
		}
		post.abort();
		return sb.toString();
	}

	/**
	 * 
	 * 
	 * @param url
	 * @param param
	 * @param file
	 * @return 
	 * @throws Exception
	 */
	private String doPost(String url, Map<String, String> param, File file)
			throws Exception {
		HttpPost post = new HttpPost(url);

		HttpClient client = new DefaultHttpClient();
		MultipartEntity entity = new MultipartEntity();
		if (param != null && !param.isEmpty()) {
			for (Map.Entry<String, String> entry : param.entrySet()) {
				entity.addPart(entry.getKey(), new StringBody(entry.getValue()));
			}
		}
		// 添加文件参数
		if (file != null && file.exists()) {
			entity.addPart("file", new FileBody(file));
		}
		post.setEntity(entity);
		HttpResponse response = client.execute(post);
		int stateCode = response.getStatusLine().getStatusCode();
		StringBuffer sb = new StringBuffer();
		if (stateCode == HttpStatus.SC_OK) {
			HttpEntity result = response.getEntity();
			if (result != null) {
				InputStream is = result.getContent();
				BufferedReader br = new BufferedReader(
						new InputStreamReader(is));
				String tempLine;
				while ((tempLine = br.readLine()) != null) {
					sb.append(tempLine);
				}
			}
		}
		post.abort();
		return sb.toString();
	}

	private String doGet(String url) {
		StringBuilder sb = new StringBuilder();
		try {
			HttpGet get = new HttpGet(url);
			// HttpPost post = new HttpPost(url);

			HttpClient client = new DefaultHttpClient();
			HttpResponse response = client.execute(get);
			StatusLine state = response.getStatusLine();
			if (state.getStatusCode() == HttpStatus.SC_OK) {
				HttpEntity eneity = response.getEntity();
				BufferedReader br = new BufferedReader(new InputStreamReader(
						eneity.getContent()));
				String content;
				while ((content = br.readLine()) != null) {
					sb.append(content);
				}
			}
			get.abort();
		} catch (Exception e) {
			e.printStackTrace();
			return sb.toString();
		}
		return sb.toString();
	}
}
