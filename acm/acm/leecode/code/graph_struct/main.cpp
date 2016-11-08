#include <QCoreApplication>
#include<iostream>
using namespace std;
enum GraphKind{DGraph,UDGraph,DNet,UDNet};
template <class VexType,class ArcType> class Graph{
protected:
    int vex_num,arc_num;
    GraphKind g_kind;
public:
    virtual int get_vexnum(){
        return vex_num;
    }
    virtual int get_arcnum(){
        return arc_num;
    }
    GraphKind & get_gkind(){
        return g_kind;
    }
    virtual void destroy()=0;
    virtual int locate_vex(VexType &value)=0;
    virtual int put_vexvalue(VexType &value)=0;
    virtual VexType & get_vex(int v)=0;
    virtual int first_adjvex(int v)=0;
    virtual int next_adjvex(int v)=0;
    virtual int insert_arc(int v,int u,ArcType weight)=0;
    virtual int delete_arc(int v,int u)=0;
    virtual int DFSTraverse(int v,void(*visitfun)(VexType x))=0;
    virtual int BFSTraverse(int v,void(*visitfun)(VexType x))=0;
};

const int max_vexnum=100;
template <class VexType,class ArcType> class MGraph:public Graph<VexType,ArcType>{
private:
    VexType *vex_list;
    ArcType ** adj_matrix;
    ArcType no_edge;
    void DFSTraverse(int v,int *visited,void(*visitfun)(VexType x));
public:
    MGraph(GraphKind kind,ArcType no_edge,int vex_size=max_vexnum);//gouzaohanshu
    ~MGraph(){
        destroy();
    }
    void destroy();
    ArcType & get_arc(int row,int col){
        return adj_matrix[row-1][col-1];
    }
    ArcType & get_noedge(){
        return no_edge;
    }
    int put_vexvalue(int v,VexType &value);
    int locate_vex(VexType &value);
    VexType &get_vex(int v){
        return vex_list[v-1];
    }
    int first_adjvex(int v);
    int next_adjvex(int v,int u);
    void insert_vex(VexType &value);
    int insert_arc(int v,int u,ArcType weight);
    void delete_vex(int v);
    int delete_arc(int v, int u);
    virtual void DFSTraverse(int v,void (*visitfun)(VexType x));
    virtual void BFSTraverse(int v,void (*visitfun)(VexType x));


};


template <class VexType,class ArcType>MGraph<VexType,ArcType>::MGraph(GraphKind kind,ArcType no_edge,int vex_size){
    this->vex_num=vex_size;
    this->g_kind=kind;
    this->no_edge=no_edge;
    this->arc_num=0;
    vex_list=new VexType[this->vex_num];
    for(int i=0;i<this->vex_num;i++){
        adj_matrix[i]=new ArcType[this->vex_num];
        for(int j=0;j<this->vex_num;j++)
            adj_matrix[i][j]=no_edge;
    }
}

//destroy the graph
template <class VexType ,class ArcType>void MGraph<VexType,ArcType>::destroy(){
    for(int i=0;i<this->vex_num;i++){
        delete []adj_matrix[i];

    }
    delete []adj_matrix;
    delete []vex_list;
    this->vex_num=this->arc_num=0;
    vex_list=NULL;
    adj_matrix=NULL;
}

template <class VexType,class ArcType>int MGraph<VexType,ArcType>::put_vexvalue(int v,VexType &value){
    if(v>0&&v<this->vex_num){
        vex_list[v-1]=value;
        return 1;
    }
    else
        return 0;
}

template <class VexType,class ArcType>int MGraph<VexType,ArcType>::locate_vex(VexType &value){
    if(this->vex_num==0)
        return -1;
    int i=0;
    while(i<this->vex_num&&value!=vex_list[i]){
        i++;
    }
    if(i<this->vex_num)
        return i;
    else
        return -1;
}

template <class VexType,class ArcType>int MGraph<VexType,ArcType>::first_adjvex(int v){
    if(v>0&&v<this->vex_num){
        for(int col=0;col<this->vex_num;col++){
            if(adj_matrix[v-1][col]!=no_edge)
                return col+1;
        }
    }
    return 0;
}

template <class VexType,class ArcType>int MGraph<VexType,ArcType>::next_adjvex(int v,int u){
    if(v>0&&u>0&&v<this->vex_num&&u<this->vex_num){
        for(int col=u;col<this->vex_num;col++){
            if(adj_matrix[v-1][col]!=no_edge)
                return col+1;
        }
    }
    return 0;
}
template <class VexType,class ArcType>int MGraph<VexType,ArcType>::insert_arc(int v,int u,ArcType weight){
    if(v<1||u<1||v>this->vex_num||u>this->vex_num)
        return 0;
    if(adj_matrix[v-1][u-1]!=no_edge)
        return 0;
    adj_matrix[v-1][u-1]=weight;
    if(this->g_kind==UDGraph||this->g_kind==UDNet)
        adj_matrix[u-1][v-1]=weight;//bidictionary
    this->arc_num++;
    return 1;
}
template <class VexType,class ArcType>int MGraph<VexType,ArcType>::delete_arc(int v,int u){
    if(v<1||u<1||v>this->vex_num||u>this->vex_num)
        return 0;
    if(adj_matrix[v-1][u-1]==no_edge)
        return 0;
    adj_matrix[v-1][u-1]=no_edge;
    if(this->g_kind==UDGraph||this->g_kind==UDNet)
        adj_matrix[u-1][v-1]=no_edge;
    this->arc_num--;
    return 1;
}

template <class ArcType>
struct arc_node_type{
    int adj_vex;
    ArcType weight;
    arc_node_type *next;
    arc_node_type(){
        next=NULL;
    }
    arc_node_type(int node,ArcType cost);
};

template <class ArcType>
arc_node_type<ArcType>::arc_node_type(int node,ArcType cost){
    adj_vex=node;
    weight=cost;
    next=NULL;
}

//template <class ArcType>
//arc_node_type<ArcType>::arc_node_type(int node, ArcType cost){
//    adj_vex=node;
//    weight=cost;
//    next=NULL;
//}

template <class VexType,class ArcType>
struct v_type{
    VexType data;
    arc_node_type <ArcType> *firstarc;
};

template <class VexType,class ArcType>
class adj_listgraph:public Graph<VexType,ArcType>{
private:
    v_type<VexType,ArcType> *v_list;
    void DFSTraverse(int v,int *visited,void (*visitfun)(VexType x));
public:
    adj_listgraph(GraphKind kind,int vex_size=max_vexnum);
    ~adj_listgraph(){
        destroy();
    }
    void destroy();
    arc_node_type<ArcType> *get_farstarc(int v){
        return v_list[v-1].firstarc;
    }
    arc_node_type<ArcType> *get_vexnode(int v){
        return v_list[v-1];
    }
    int first_adjvex(int v);
    int next_adjvex(int v,int u);
    int put_vexvalue(int v,VexType &value);
    int locate_vex(VexType &value);
    VexType &get_vex(int v){
        return v_list[v-1].data;
    }
    int insert_arc(int v, int u, ArcType cost);
    int delete_arc(int v, int u);
    void DFSTraverse(int v, void (*visitfun)(VexType x));
    void BFSTraverse(int v, void (*visitfun)(VexType x));

};

template <class VexType,class ArcType>adj_listgraph<VexType,ArcType>::adj_listgraph(GraphKind kind,int vex_size){
    this->vex_num=vex_size;
    this->g_kind=kind;
    this->arc_num=0;
    v_list=new VexType<VexType,ArcType>[this->vex_num];
    for(int i=0;i<this->vex_num;i++){
        v_list[i].firstarc=NULL;
    }
}

template <class VexType,class ArcType>void adj_listgraph<VexType,ArcType>::destroy(){
    for(int i=0;i<this->vex_num;i++){
        arc_node_type<ArcType> *p=v_list[i].firstarc;
        while(p){
            arc_node_type<ArcType> *q=p->next;
            delete p;
            p=q;
        }

    }
    delete []v_list;
    this->vex_num=this->arc_num=0;
    v_list=NULL;
}

template <class VexType,class ArcType>int adj_listgraph<VexType,ArcType>::put_vexvalue(int v,VexType &value){
    if(v>0||v<this->vex_num){
        v_list[v-1].data=value;
        return 1;
    }
    else
        return 0;
}

template <class VexType,class ArcType>int adj_listgraph<VexType,ArcType>::locate_vex(VexType &value){
    if(this->vex_num==0){
        return -1;
    }
    int i=0;
    while(i<this->vex_num&&value!=v_list[i].data)
        i++;
    if(i<this->vex_num)
        return i;
    else
        return -1;
}

template <class VexType,class ArcType>int adj_listgraph<VexType,ArcType>::first_adjvex(int v){
    if(v<this->vex_num&&v<=this->vex_num){
        arc_node_type<ArcType> *p=v_list[v-1].firstarc;
        if(p)
            return p->adj_vex+1;
    }
    return 0;
}

template <class VexType,class ArcType>int adj_listgraph<VexType,ArcType>::next_adjvex(int v,int u){
    if(v>0&&v<=this->vex_num){
        arc_node_type<ArcType> *p=v_list[v-1].firstarc;
        while(p){
            if(p->adj_vex+1==u&&p->next)
                return p->next->adj_vex+1;
            else
                p=p->next;
        }
    }
    return 0;
}

template <class VexType,class ArcType>int adj_listgraph<VexType,ArcType>::insert_arc(int v,int u,ArcType cost){
    if(v<1||u<1||v>this->vex_num||u>this->vex_num)
        return 0;
    arc_node_type <ArcType> *q;
    q=new arc_node_type<ArcType>
}




int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    return a.exec();
}
