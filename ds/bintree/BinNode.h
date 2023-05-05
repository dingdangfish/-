#define BinNodePosi(T) BinNode<T> * //�ڵ�λ��
#define stature(p) ((p) ? (p)->height : -1) //�ڵ�߶ȣ����������߶�Ϊ-1���mԼ����ͳһ��
typedef enum { RB_RED, RB_BLACK } RBColor; //�ڵ���ɫ
template <typename T> struct BinNode { //�������ڵ�ģ����
	// ��Ա��Ϊ���������ͳһ���ţ����߿ɸ�����Ҫ��һ����װ��
		T data; //��ֵ
	BinNodePosi(T) parent; BinNodePosi(T) lc; BinNodePosi(T) rc; //���ڵ㼰���Һ���
	int height; //�߶ȣ�ͨ�ã�
    int npl; //Null Path Length����ʽ�ѣ�Ҳ��ֱ����height���棩
	RBColor color; //��ɫ���������
	// ���캯��
		BinNode() :
		parent(NULL), lc(NULL), rc(NULL), height(0), npl(1), color(RB_RED) { }
	BinNode(T e, BinNodePosi(T) p = NULL, BinNodePosi(T) lc = NULL, BinNodePosi(T) rc = NULL,
		int h = 0, int l = 1, RBColor c = RB_RED) :
		data(e), parent(p), lc(lc), rc(rc), height(h), npl(l), color(c) { }
	// �����ӿ�
		int size(); //ͳ����ǰ�ڵ����������༴����Ϊ���m�����m�_ģ
	BinNodePosi(T) insertAsLC(T const&); //��Ϊ��ǰ�ڵ�m���ӓI���½ڵ�
	BinNodePosi(T) insertAsRC(T const&); //��Ϊ��ǰ�ڵ�m�Һ��ӓI���½ڵ�
	BinNodePosi(T) succ(); //����ǰ�ڵ�mֱ�Ӻ��
	template <typename VST> void travLevel(VST&); //�����ִα���
	template <typename VST> void travPre(VST&); //�����������
	template <typename VST> void travIn(VST&); //�����������
	template <typename VST> void travPost(VST&); //�����������
	// �Ƚ������`������������һ���������в��䣩
		bool operator< (BinNode const& bn) { return data < bn.data; } //Сء
	bool operator== (BinNode const& bn) { return data == bn.data; } //��ء
};
