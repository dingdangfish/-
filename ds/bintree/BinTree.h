#include "BinNode.h"
#include<Stack>
template <typename T> class BinTree {
protected:
	int _size; BinNodePosi(T) _root; //��ģ�����ڵ�
	virtual int updateHeight(BinNodePosi(T) x); //���½ڵ�x�ĸ߶�
	void updateHeightAbove(BinNodePosi(T) x); //���½ڵ�x�������ȵĸ߶�
public:
	BinTree() : _size(0), _root(NULL) { } //���캯��
	~BinTree() { if (0 < _size) remove(_root); } //��������
	int size() const { return _size; } //��ģ
	bool empty() const { return !_root; } //�п�
	BinNodePosi(T) root() const { return _root; } //����
	BinNodePosi(T) insertAsRoot(T const& e); //������ڵ�
	BinNodePosi(T) insertAsLC(BinNodePosi(T), T const& e); //��������
	BinNodePosi(T) insertAsRC(BinNodePosi(T), T const& e); //�����Һ���
	BinNodePosi(T) attachAsLC(BinNodePosi(T), BinTree<T>*& T); //����������
	BinNodePosi(T) attachAsRC(BinNodePosi(T), BinTree<T>*& T); //����������
	int remove(BinNodePosi(T) x); //ɾ����xΪ���ڵ�����������ظ�����ԭ�ȵĹ�ģ
	BinTree<T>* secede(BinNodePosi(T) x); //������x�ӵ�ǰ����ժ����������ת����һ�ö���������
	template < typename VST> //������
	void travLevel(VST& visit) { if (_root) _root->travLevel(visit); } //��α���
	template < typename VST> //������
	void travPre(VST& visit) { if (_root) _root->travPre(visit); } //�������
	template < typename VST> //������
	void travIn(VST& visit) { if (_root) _root->travIn(visit); } //�������
	template < typename VST> //������
	void travPost(VST& visit) { if (_root) _root->travPost(visit); } //�������

	bool operator< (BinTree<T> const& t) //�Ƚ���
	{
		return _root && t._root && (_root->data < t._root->data);
	}
	bool operator> (BinTree<T> const& t) //�Ƚ���
	{
		return _root && t._root && (_root->data > t._root->data);
	}
	bool operator== (BinTree<T> const& t) //�е���
	{
		return _root && t._root && (_root == t._root);
	}
	bool operator!= (BinTree<T> const& t) //�е���
	{
		return _root && t._root && (_root != t._root);
	}
}; //BinTree

//��С�Ƚ�
int max(int x, int y) {
	return x > y ? x : y;
}
//���½ڵ�x�߶�
template <typename T> int BinTree<T>::updateHeight(BinNodePosi(T) x)
{													//���������������
	return x->height = 1 + max(stature(x->lc), stature(x->rc));
}
//�����������ȸ߶�
template <typename T> void BinTree<T>::updateHeightAbove(BinNodePosi(T) x)
{
	while (x) {
		if (x->height == updateHeight(x)) break;
		//��ǰ�ڵ�ĸ߶�����º�Ľڵ�߶���ͬ�����������ϸ����ˣ��Ըýڵ���˵���仯�Ľڵ㲻�Ǳ��ڵ������·���ڵ�
		updateHeight(x);
		x = x->parent;
	}
} //��x�����������������ȡ�
//��e�������ڵ����յĶ�����
template <typename T> BinNodePosi(T) BinTree<T>::insertAsRoot(T const& e)
{
	_size = 1; return _root = new BinNode<T>(e);
}
//e����Ϊx������
template <typename T> BinNodePosi(T) BinTree<T>::insertAsLC(BinNodePosi(T) x, T const& e)
{
	_size++; x->insertAsLC(e); updateHeightAbove(x); return x->lc;
}
//e����Ϊx���Һ���
template <typename T> BinNodePosi(T) BinTree<T>::insertAsRC(BinNodePosi(T) x, T const& e)
{
	_size++; x->insertAsRC(e); updateHeightAbove(x); return x->rc;
}
//ɾ����������λ��x���Ľڵ㼰���������ر�ɾ���ڵ����ֵ
template < typename T> int BinTree<T>::remove(BinNodePosi(T) x) { //xΪ�������еĺϷ�λ��
	FromParentTo(*x) = NULL; //�ж����Ը��ڵ��ָ��
	updateHeightAbove(x->parent); //�������ȸ߶�
	int n = removeAt(x); _size -= n; return n; //ɾ������x�����¹�ģ������ɾ���ڵ�����
}
//�ͷŽڵ�ֵ
template <typename T>void release(T& e) {
	e = NULL;
}
//�ͷŽڵ�ռ�
template <typename T>void release(BinNodePosi(T)& e) {
	delete e;
}
//ɾ����������λ��x���Ľڵ㼰���������ر�ɾ���ڵ����ֵ
template <typename T> static int removeAt(BinNodePosi(T) x) { //xΪ�������еĺϷ�λ��
	if (!x) return 0; //�ݹ��������
	int n = 1 + removeAt(x->lc) + removeAt(x->rc); //�ݹ��ͷ���������
	release(x->data); release(x); return n; //�ͷű�ժ���ڵ㣬������ɾ���ڵ�����
}
//��S�����ڵ�x�������������������S�����ÿ�
template < typename T> BinNodePosi(T) BinTree<T>::attachAsLC(BinNodePosi(T) x, BinTree<T>*& S) { //x->lc == NULL
	if (x->lc = S->_root) x->lc->parent = x; //����
	_size += S->_size; updateHeightAbove(x); //����ȫ����ģ��x�������ȵĸ߶�
	S->_root = NULL; S->_size = 0; release(S); S = NULL; return x; //�ͷ�ԭ�������ؽ���λ��
}
//��S�����ڵ�x�������������������S�����ÿ�
template <typename T>  BinNodePosi(T) BinTree<T>::attachAsRC(BinNodePosi(T) x, BinTree<T>*& S) { //x->rc == NULL
	if (x->rc = S->_root) x->rc->parent = x; //����
	_size += S->_size; updateHeightAbove(x); //����ȫ����ģ��x�������ȵĸ߶�
	S->_root = NULL; S->_size = 0; release(S); S = NULL; return x; //�ͷ�ԭ�������ؽ���λ��
}
//���������������㷨��������x�ӵ�ǰ����ժ���������װΪһ�ö�����������
template < typename T> BinTree<T>*BinTree<T>::secede(BinNodePosi(T) x) { //xΪ�������еĺϷ�λ��
	FromParentTo(*x) = NULL; //�ж����Ը��ڵ��ָ��
	updateHeightAbove(x->parent); //����ԭ�����������ȵĸ߶�
	BinTree<T>* S = new BinTree<T>; S->_root = x; x->parent = NULL; //������xΪ��
	S->_size = x->size(); _size -= S->_size; return S; //���¹�ģ�����ط������������
}

//���ʽڵ������
template <typename T>void visits(T e) {
	std::cout << e << " ";
}
//�ӵ�ǰ�ڵ�����������֧�������룬ֱ��û�����֧�Ľڵ㣻��;�ڵ���������������

