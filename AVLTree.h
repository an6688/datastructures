#ifndef AVLTREE_H
#define AVLTREE_H

#include <functional>

#include "AvlNode.h"
#include "ListQueue.h"
#include "AdtException.h"
#include "ITree.h"

using std::function;

template <class K, class V>
class AVLTree : ITree<K, V>
{
public:
	AVLTree() = default;
	AVLTree(const AVLTree& copy) noexcept(false);
	~AVLTree();
	AVLTree<K, V> & operator=(const AVLTree<K, V>& rhs) noexcept(false);
	AVLTree(AVLTree && copy) noexcept;
	AVLTree<K, V> & operator=(AVLTree<K, V> && rhs) noexcept(false);
	void SetVisitFunction(function<void(const AVLNode<K, V> * const node)> visit);
	void Clear() noexcept override;
	size_t Height() noexcept override;
	bool IsEmpty() const noexcept override;
	void InOrder() const noexcept override;
	void PreOrder() const noexcept override;
	void PostOrder() const noexcept override;
	void BreadthFirst() const noexcept override;
	void Insert(K key, V value) noexcept(false) override;
	void Delete(const K& key) noexcept(false) override;
	V Search(const K& key) const noexcept(false) override;
	V& Search(const K& key) noexcept(false) override;
	size_t GetCount() const;

private:
	AVLNode<K, V>* root_ = nullptr;
	function<void(const AVLNode<K, V> * const node)> visit_;
	size_t tree_count_ = 0;
#endif
