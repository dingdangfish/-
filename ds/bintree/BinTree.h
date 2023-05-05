#include "BinNode.h"
#include<Stack>
template <typename T> class BinTree {
protected:
	int _size; BinNodePosi(T) _root; //规模、根节点
	virtual int updateHeight(BinNodePosi(T) x); //更新节点x的高度
	void updateHeightAbove(BinNodePosi(T) x); //更新节点x及其祖先的高度
public:
	BinTree() : _size(0), _root(NULL) { } //构造函数
	~BinTree() { if (0 < _size) remove(_root); } //析构函数
	int size() const { return _size; } //规模
	bool empty() const { return !_root; } //判空
	BinNodePosi(T) root() const { return _root; } //树根
	BinNodePosi(T) insertAsRoot(T const& e); //插入根节点
	BinNodePosi(T) insertAsLC(BinNodePosi(T), T const& e); //插入左孩子
	BinNodePosi(T) insertAsRC(BinNodePosi(T), T const& e); //插入右孩子
	BinNodePosi(T) attachAsLC(BinNodePosi(T), BinTree<T>*& T); //接入左子树
	BinNodePosi(T) attachAsRC(BinNodePosi(T), BinTree<T>*& T); //接入右子树
	int remove(BinNodePosi(T) x); //删除以x为根节点的子树，返回该子树原先的规模
	BinTree<T>* secede(BinNodePosi(T) x); //将子树x从当前树中摘除，并将其转化成一棵独立的子树
	template < typename VST> //操作器
	void travLevel(VST& visit) { if (_root) _root->travLevel(visit); } //层次遍历
	template < typename VST> //操作器
	void travPre(VST& visit) { if (_root) _root->travPre(visit); } //先序遍历
	template < typename VST> //操作器
	void travIn(VST& visit) { if (_root) _root->travIn(visit); } //中序遍历
	template < typename VST> //操作器
	void travPost(VST& visit) { if (_root) _root->travPost(visit); } //后序遍历

	bool operator< (BinTree<T> const& t) //比较器
	{
		return _root && t._root && (_root->data < t._root->data);
	}
	bool operator> (BinTree<T> const& t) //比较器
	{
		return _root && t._root && (_root->data > t._root->data);
	}
	bool operator== (BinTree<T> const& t) //判等器
	{
		return _root && t._root && (_root == t._root);
	}
	bool operator!= (BinTree<T> const& t) //判等器
	{
		return _root && t._root && (_root != t._root);
	}
}; //BinTree

//大小比较
int max(int x, int y) {
	return x > y ? x : y;
}
//更新节点x高度
template <typename T> int BinTree<T>::updateHeight(BinNodePosi(T) x)
{													//具体规则，因树而异
	return x->height = 1 + max(stature(x->lc), stature(x->rc));
}
//更新所有祖先高度
template <typename T> void BinTree<T>::updateHeightAbove(BinNodePosi(T) x)
{
	while (x) {
		if (x->height == updateHeight(x)) break;
		//当前节点的高度与更新后的节点高度相同，不用再向上更新了，对该节点来说，变化的节点不是本节点的最深路径节点
		updateHeight(x);
		x = x->parent;
	}
} //从x出发，覆盖历代祖先。
//将e当作根节点插入空的二叉树
template <typename T> BinNodePosi(T) BinTree<T>::insertAsRoot(T const& e)
{
	_size = 1; return _root = new BinNode<T>(e);
}
//e插入为x的左孩子
template <typename T> BinNodePosi(T) BinTree<T>::insertAsLC(BinNodePosi(T) x, T const& e)
{
	_size++; x->insertAsLC(e); updateHeightAbove(x); return x->lc;
}
//e插入为x的右孩子
template <typename T> BinNodePosi(T) BinTree<T>::insertAsRC(BinNodePosi(T) x, T const& e)
{
	_size++; x->insertAsRC(e); updateHeightAbove(x); return x->rc;
}
//删除二叉树中位置x处的节点及其后代，返回被删除节点的数值
template < typename T> int BinTree<T>::remove(BinNodePosi(T) x) { //x为二叉树中的合法位置
	FromParentTo(*x) = NULL; //切断来自父节点的指针
	updateHeightAbove(x->parent); //更新祖先高度
	int n = removeAt(x); _size -= n; return n; //删除子树x，更新规模，返回删除节点总数
}
//释放节点值
template <typename T>void release(T& e) {
	e = NULL;
}
//释放节点空间
template <typename T>void release(BinNodePosi(T)& e) {
	delete e;
}
//删除二叉树中位置x处的节点及其后代，返回被删除节点的数值
template <typename T> static int removeAt(BinNodePosi(T) x) { //x为二叉树中的合法位置
	if (!x) return 0; //递归基：空树
	int n = 1 + removeAt(x->lc) + removeAt(x->rc); //递归释放左、右子树
	release(x->data); release(x); return n; //释放被摘除节点，并返回删除节点总数
}
//将S当作节点x的左子树接入二叉树，S本身置空
template < typename T> BinNodePosi(T) BinTree<T>::attachAsLC(BinNodePosi(T) x, BinTree<T>*& S) { //x->lc == NULL
	if (x->lc = S->_root) x->lc->parent = x; //接入
	_size += S->_size; updateHeightAbove(x); //更新全树规模与x所有祖先的高度
	S->_root = NULL; S->_size = 0; release(S); S = NULL; return x; //释放原树，返回接入位置
}
//将S当作节点x的右子树接入二叉树，S本身置空
template <typename T>  BinNodePosi(T) BinTree<T>::attachAsRC(BinNodePosi(T) x, BinTree<T>*& S) { //x->rc == NULL
	if (x->rc = S->_root) x->rc->parent = x; //接入
	_size += S->_size; updateHeightAbove(x); //更新全树规模与x所有祖先的高度
	S->_root = NULL; S->_size = 0; release(S); S = NULL; return x; //释放原树，返回接入位置
}
//二叉树子树分离算法：将子树x从当前树中摘除，将其封装为一棵独立子树返回
template < typename T> BinTree<T>*BinTree<T>::secede(BinNodePosi(T) x) { //x为二叉树中的合法位置
	FromParentTo(*x) = NULL; //切断来自父节点的指针
	updateHeightAbove(x->parent); //更新原树中所有祖先的高度
	BinTree<T>* S = new BinTree<T>; S->_root = x; x->parent = NULL; //新树以x为根
	S->_size = x->size(); _size -= S->_size; return S; //更新规模，返回分离出来的子树
}

//访问节点的数据
template <typename T>void visits(T e) {
	std::cout << e << " ";
}
//从当前节点出发，沿左分支不断深入，直至没有左分支的节点；沿途节点遇到后立即访问

