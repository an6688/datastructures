#pragma once

#include <PairNode.h>

template <class K, class V>
class AVLNode : public PairNode<K, V>
{
public:
	explicit AVLNode<K, V>(const K key, const V value, AVLNode<K, V> * left = nullptr, AVLNode<K, V> * right = nullptr) noexcept;
	~AVLNode() = default;
	AVLNode<K, V>(const AVLNode<K, V> & copy) noexcept;
	AVLNode<K, V> & operator=(const AVLNode<K, V> & rhs);
	AVLNode<K, V>(AVLNode<K, V> && copy) noexcept;
	AVLNode<K, V> & operator=(AVLNode<K, V> && rhs) noexcept;
	AVLNode<K, V> *& GetLeft() noexcept;
	AVLNode<K, V> *& GetRight() noexcept;
	AVLNode<K, V> * GetLeft() const noexcept;
	AVLNode<K, V> * GetRight() const noexcept;
	void SetLeft(AVLNode<K, V> * const left) noexcept;
	void SetRight(AVLNode<K, V> * const right) noexcept;

private:
	AVLNode<K, V> * left_ = nullptr;
	AVLNode<K, V> * right_ = nullptr;

};
#endif
