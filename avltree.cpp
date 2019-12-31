//  AVL Tree


#include <iostream> //to use cout
#include <algorithm> //to use max function such as  i = max(a, b);

using namespace std;

//use the following node class for each node of the AVL tree
class node {
public:
	int value;
	int height;
	bool is_left_child; //true if this node is the left child of its parent node; else false;
	bool is_right_child; //true if this node is the right child of its parent node; else false;
	node * parent;
	node * l_child;
	node * r_child;
	node() {}
	node(int i) {
		value = i; height = 1; parent = l_child = r_child = nullptr;
		is_left_child = is_right_child = false;
	}

};

class avl_tree {
public:
	node * root;
	avl_tree() {
		root = nullptr;
	}
	void add_node(int i);//You need to implement this.
	//When there is a tie of values, continue the search toward the child branch with smaller height.
	//If both left and right child branch carry the same height, continue the search toward the right child branch.



	void in_order_traversal(node *p);  //provided.


	void height_adjustment(node *p, node * &action_node_pointer, int &pattern); //
	/*
    //
	This function is invoked by add_node and remove_node.
	p points to the first node that we need to check for possible height update.  We then need to check possible height update toward root.
	All nodes whose heights need to be updated will be performed in this function.
	When invoked, action_node_pointer = nullptr, pattern = 0.
	If no imbalance is detected, action_node_pointer remains nullptr, and pattern remains 0.
	If an imbalance is detected, the action_node_pointer will carry the address of acation node and
	pattern will be set to 11, 12, 22, 21 for LL, LR, RR and RL, respectively.
	*/


	void L_Rotate(node *p); 
	//p points to the node around which the rotation will be performed.

	void R_Rotate(node *p); 
	//p points to the node around which the rotation will be performed.

	void remove_node(int i);
	//Remove the node with value i.  Assume that all node values are distinct.
	//Many of the above functions will be invoked bny remove_node as well.
	//You need to implement the approach one mentioned in class.
	//The child branch with larger height will be moved up to the position of the deleted node
	//If the two child branches have the same height, move the right branch up.
	//You need to take care of the exception case described in class.
	//If more than one node carries the value to be deleted, only the node encountered first during search
	//will be deleted.

};
void avl_tree::remove_node(int i)
{
	node*p = root;
	while (true)
	{
		if (p->value > i)
		{
			if (p->l_child != nullptr)
			{
				p = p->l_child;
				continue;
			}
		}
		else if (p->value < i)
		{
			if (p->r_child != nullptr)
			{
				p = p->r_child;
				continue;
			}
		}
		else
		{
			break;
		}
	}

	node* an = nullptr;
	int pattern = 0;
	if (p->value == i)
	{
		if (p->height == 1)
		{
			node * r = p->parent;

			if (p->is_right_child)
			{
				p = p->parent;
				delete p->r_child;
				p->r_child = nullptr;
			}
			else if (p->is_left_child)
			{
				p = p->parent;
				delete p->l_child;
				p->l_child = nullptr;
			}
			else if (p == root)
			{
				delete p;
				p = nullptr;
				root = nullptr;
			}
			if (r != nullptr)
			{
				
				height_adjustment(r, an, pattern);
			}
		}

		else if (p->l_child != nullptr && p->r_child == nullptr)
		{
			node* t = p->l_child;
			node * r = p->parent;
			if (p == root)
			{
				t->parent = nullptr;
				t->is_left_child = false;
				p->l_child = nullptr;
				delete p;
				p = nullptr;
				root = t;
				
			}
			else if (p->is_left_child)
			{
				r->l_child = t;
				t->parent = r;
				t->is_left_child = true;
				t->is_right_child = false;
				delete p;
				p = nullptr;
				height_adjustment(r, an, pattern);
			}
			else if (p->is_right_child)
			{
				r->r_child = t;
				t->parent = r;
				t->is_right_child = true;
				t->is_left_child = false;
				delete p;
				p = nullptr;
				height_adjustment(r, an, pattern);
			}
			
		}

		else if (p->l_child == nullptr && p->r_child != nullptr)
		{
			node* t = p->r_child;
			node * r = p->parent;

			if (p == root)
			{
				t->parent = nullptr;
				t->is_right_child = false;
				p->r_child = nullptr;
				delete p;
				p = nullptr;
				root = t;
				
			}
			else if (p->is_left_child)
			{
				r->l_child = t;
				t->parent = r;
				t->is_left_child = true;
				t->is_right_child = false;
				delete p;
				p = nullptr;
				height_adjustment(r, an, pattern);
			}
			else if (p->is_right_child)
			{
				r->r_child = t;
				t->parent = r;
				t->is_left_child = false;
				t->is_right_child = true;
				delete p;
				p = nullptr;
				height_adjustment(r, an, pattern);
			}
		}

		else if (p->l_child != nullptr && p->r_child != nullptr)
		{
			if (p->l_child->height > p->r_child->height)
			{
				node* r = p->parent;
				node * left = p->l_child;
				node * right = p->r_child;
				if (r == nullptr)
				{
					if (left->r_child == nullptr)
					{
						left->r_child = right;
						right->parent = left;
						right->is_right_child = true;
						right->is_left_child = false;
						delete p;
						p = nullptr;
						root = left;
						left->is_left_child = false;
						left->is_right_child = false;
						left->parent = nullptr;
						height_adjustment(left, an, pattern);
					}
					else if (left->r_child != nullptr)
					{
						node *q = left->r_child;
						left->r_child = right;
						right->parent = left;
						right->is_right_child = true;
						right->is_left_child = false;
						node * h = right;
						while (h->l_child != nullptr)
						{
							h = h->l_child;
						}
						h->l_child = q;
						q->parent = h;
						q->is_left_child = true;
						q->is_right_child = false;
						delete p;
						p = nullptr;
						root = left;
						left->is_left_child = false;
						left->is_right_child = false;
						left->parent = nullptr;
						height_adjustment(q, an, pattern);
					}
				}
				else if (p->is_right_child)
				{
					r->r_child = left;
					left->parent = r;
					left->is_right_child = true;
					left->is_left_child = false;
					if (left->r_child != nullptr)
					{
						node *q = left->r_child;
						right->parent = left;
						left->r_child = right;
						right->is_right_child = true;
						right->is_left_child = false;
						node *h = right;
						while (h->l_child != nullptr)
						{
							h = h->l_child;
						}
						h->l_child = q;
						q->parent = h;
						q->is_left_child = true;
						q->is_right_child = false;
						delete p;
						p = nullptr;
						height_adjustment(q, an, pattern);
					}
					else if (left->r_child == nullptr)
					{
						left->r_child = right;
						right->parent = left;
						right->is_right_child = true;
						right->is_left_child = false;
						delete p;
						p = nullptr;
						height_adjustment(left, an, pattern);
					}
				}
				else if (p->is_left_child)
				{
					r->l_child = left;
					left->parent = r;
					left->is_left_child = true;
					left->is_right_child = false;
					if (left->r_child != nullptr)
					{
						node*q = left->r_child;
						right->parent = left;
						left->r_child = right;
						right->is_right_child = true;
						right->is_left_child = false;
						node* h = right;
						while (h->l_child != nullptr)
						{
							h = h->l_child;
						}
						h->l_child = q;
						q->parent = h;
						q->is_left_child = true;
						q->is_right_child = false;
						delete p;
						p = nullptr;
						height_adjustment(q, an, pattern);
					}
					else if (left->r_child == nullptr)
					{
						left->r_child = right;
						right->parent = left;
						right->is_right_child = true;
						right->is_left_child = false;
						delete p;
						p = nullptr;
						height_adjustment(left, an, pattern);
					}
				}
			}

			else if (p->r_child->height >= p->l_child->height)
			{
				node* r = p->parent;
				node * left = p->l_child;
				node *right = p->r_child;
				if (r == nullptr)
				{
					if (right->l_child == nullptr)
					{
						right->l_child = left;
						left->parent = right;
						left->is_left_child = true;
						left->is_right_child = false;
						delete p;
						p = nullptr;
						root = right;
						right->is_left_child = false;
						right->is_right_child = false;
						right->parent = nullptr;
						height_adjustment(right, an, pattern);
					}
					else if (right->l_child != nullptr)
					{
						node *q = right->l_child;
						right->l_child = left;
						left->parent = right;
						left->is_left_child = true;
						left->is_right_child = false;
						node * h = left;
						while (h->r_child != nullptr)
						{
							h = h->r_child;
						}
						h->r_child = q;
						q->parent = h;
						q->is_right_child = true;
						q->is_left_child = false;
						delete p;
						p = nullptr;
						root = right;
						right->parent = nullptr;
						right->is_left_child = false;
						right->is_right_child = false;
						height_adjustment(q, an, pattern);
					}
				}
				else if (p->is_left_child)
				{
					r->l_child = right;
					right->parent = r;
					right->is_left_child = true;
					right->is_right_child = false;
					if (right->l_child != nullptr)
					{
						node *q = right->l_child;
						right->l_child = left;
						left->parent = right;
						left->is_left_child = true;
						left->is_right_child = false;
						node *h = left;
						while (h->r_child != nullptr)
						{
							h = h->r_child;
						}
						h->r_child = q;
						q->parent = h;
						q->is_right_child = true;
						q->is_left_child = false;
						delete p;
						p = nullptr;
						height_adjustment(q, an, pattern);
					}

					else if (right->l_child == nullptr)
					{
						right->l_child = left;
						left->parent = right;
						left->is_left_child = true;
						left->is_right_child = false;
						delete p;
						p = nullptr;
						height_adjustment(right, an, pattern);
					}
				}
				else if (p->is_right_child)
				{
					r->r_child = right;
					right->parent = r;
					right->is_right_child = true;
					right->is_left_child = false;
					if (right->l_child != nullptr)
					{
						node *q = right->l_child;
						right->l_child = left;
						left->parent = right;
						left->is_left_child = true;
						left->is_right_child = false;
						node *h = left;
						while (h->r_child != nullptr)
						{
							h = h->r_child;
						}
						h->r_child = q;
						q->parent = h;
						q->is_right_child = true;
						q->is_left_child = false;
						delete p;
						p = nullptr;
						height_adjustment(q, an, pattern);
					}
					else if (right->l_child == nullptr)
					{
						right->l_child = left;
						left->parent = right;
						left->is_left_child = true;
						left->is_right_child = false;
						delete p;
						p = nullptr;
						height_adjustment(right, an, pattern);
					}
				}
			}
		}


	}

	if (an != nullptr)
	{//violation 
		if (pattern == 11)
		{//L-L violation, R-rotate
			node *p = an->l_child;
			R_Rotate(p);
		}
		else if (pattern == 22)
		{//R-R violation, L-rotate
			node *p = an->r_child;
			L_Rotate(p);
		}
		else if (pattern == 12)
		{//L-R violation, L-rotate, R-rotate
			p = an->l_child->r_child;
			L_Rotate(p);
			R_Rotate(p);
		}
		else if (pattern == 21)
		{//R-L violation, R-rotate, L-rotate
			p = an->r_child->l_child;
			R_Rotate(p);
			L_Rotate(p);
		}
	}


	while (true)
	{
		node *a = an;
		an = nullptr;
		int pp = 0;
		height_adjustment(a, an, pp);
		if (an != nullptr)
		{//violation 
			if (pp == 11)
			{//L-L violation, R-rotate
				node *p = an->l_child;
				R_Rotate(p);
			}
			else if (pp == 22)
			{//R-R violation, L-rotate
				node *p = an->r_child;
				L_Rotate(p);
			}
			else if (pp == 12)
			{//L-R violation, L-rotate, R-rotate
				p = an->l_child->r_child;
				L_Rotate(p);
				R_Rotate(p);
			}
			else if (pp == 21)
			{//R-L violation, R-rotate, L-rotate
				p = an->r_child->l_child;
				R_Rotate(p);
				L_Rotate(p);
			}
		}
		else
		{
			break;
		}
	}
}
void avl_tree::add_node(int i)
{
	node * s = new node(i);
	if (root == nullptr)
	{
		root = s;
	}
	else
	{
		node *p = root;
		while (true)
		{
			if (p->value > i)
			{
				if (p->l_child != nullptr)
				{
					p = p->l_child;
					continue;
				}
				else
				{
					s->parent = p;
					p->l_child = s;
					s->is_left_child = true;
					break;
				}
			}
			else if (p->value < i)
			{
				if (p->r_child != nullptr)
				{
					p = p->r_child;
					continue;
				}
				else
				{
					s->parent = p;
					p->r_child = s;
					s->is_right_child = true;
					break;
				}
			}
			else
			{
				if (p->l_child == nullptr && p->r_child == nullptr)
				{
					s->parent = p;
					p->r_child = s;
					s->is_right_child = true;
					break;
				}
				else if (p->l_child != nullptr && p->r_child == nullptr)
				{
					s->parent = p;
					p->r_child = s;
					s->is_right_child = true;
					break;
				}
				else if (p->l_child == nullptr && p->r_child != nullptr)
				{
					s->parent = p;
					p->l_child = s;
					s->is_left_child = true;
					break;
				}
				else if (p->l_child != nullptr && p->r_child != nullptr)
				{
					if (p->l_child->height >= p->r_child->height)
					{
						p = p->r_child;
						continue;
					}
					else if (p->r_child->height > p->l_child->height)
					{
						p = p->l_child;
						continue;
					}
				}
			}

		}

		node * an = nullptr;
		int pattern = 0;
		height_adjustment(s, an, pattern);
		if (an != nullptr)
		{
			if (pattern == 11)
			{//L-L violation, R-rotate
				node *p = an->l_child;
				R_Rotate(p);
			}
			else if (pattern == 22)
			{//R-R violation, L-rotate
				node *p = an->r_child;
				L_Rotate(p);
			}
			else if (pattern == 12)
			{//L-R violation, L-rotate, R-rotate
				p = an->l_child->r_child;
				L_Rotate(p);
				R_Rotate(p);
			}
			else if (pattern == 21)
			{//R-L violation, R-rotate, L-rotate
				p = an->r_child->l_child;
				R_Rotate(p);
				L_Rotate(p);
			}
			node *a = an;
			//pattern = 0;
			height_adjustment(a, an, pattern);

		}
	}
}
void avl_tree::height_adjustment(node *p, node * &action_node_pointer, int &pattern)
{
	node * q = p;
	while (q != nullptr)
	{
		if (q->r_child == nullptr && q->l_child != nullptr)
		{
			q->height = (q->l_child->height) + 1;
		}
		else if (q->l_child == nullptr && q->r_child != nullptr)
		{
			q->height = (q->r_child->height) + 1;
		}
		else if (q->l_child != nullptr && q->r_child != nullptr)
		{
			q->height = max(q->l_child->height, q->r_child->height) + 1;
		}
		else if (q->l_child == nullptr && q->r_child == nullptr)
		{
			q->height = 1;
		}
		q = q->parent;
	}
	//AN
	q = p;
	while (q != nullptr)
	{
		if (q->height == 1)
		{
			q = q->parent;
			continue;
		}
		else if (q->r_child == nullptr && q->l_child != nullptr)
		{
			if (q->l_child->height >= 2)
			{
				action_node_pointer = q;
				node * left = q->l_child;
				if (left->l_child == nullptr)
				{
				 //L-R
					pattern = 12;
				}
				else if (left->r_child == nullptr)
				{
				 //L-L
					pattern = 11;
				}
				else if (left->r_child->height > left->l_child->height)
				{
				 //L-R
					pattern = 12;
				}
				else if (left->r_child->height <= left->l_child->height)
				{
				 //L-L
					pattern = 11;
				}
				
				break;
			}
			else
			{
				q = q->parent;
				continue;
			}
		}

		else if (q->l_child == nullptr && q->r_child != nullptr)
		{
			if (q->r_child->height >= 2)
			{
				action_node_pointer = q;
				node* right = q->r_child;
				if (right->l_child == nullptr)
				{
				 //R-R
					pattern = 22;
				}
				else if (right->r_child == nullptr)
				{
				 //R-L
					pattern = 21;
				}
				else if (right->r_child->height >= right->l_child->height)
				{
				 //R-R
					pattern = 22;
				}
				else if (right->l_child->height > right->r_child->height)
				{
				 //R-L
					pattern = 21;
				}
				break;
			}
			else
			{
				q = q->parent;
				continue;
			}
		}

		else if (q->l_child != nullptr && q->r_child != nullptr)
		{
			if ((q->r_child->height - q->l_child->height) >= 2)
			{
				action_node_pointer = q;
				node * t = q->r_child;
				if (t->r_child->height >= t->l_child->height)
				{
				 //R-R
					pattern = 22;
				}
				else if (t->l_child->height > t->r_child->height)
				{
				 //R-L
					pattern = 21;
				}
				break;
			}
			else if ((q->l_child->height - q->r_child->height) >= 2)
			{
				action_node_pointer = q;
				node * t = q->l_child;
				if (t->r_child->height > t->l_child->height)
				{
				 //L-R
					pattern = 12;
				}
				else if (t->l_child->height >= t->r_child->height)
				{
				 //L-L
					pattern = 11;
				}
				break;
			}
			else
			{
				q = q->parent;
				continue;
			}

		}
	}

}
void avl_tree::L_Rotate(node * p)
{
	node*r = p->parent;
	p->parent = r->parent;
	if (r->parent == nullptr)
	{
		root = p;
		p->is_left_child = r->is_left_child;
		p->is_right_child = r->is_right_child;
	}
	if (r->parent != nullptr)
	{
		p->is_left_child = r->is_left_child;
		p->is_right_child = r->is_right_child;
	}
	if (r->is_left_child)
	{
		r->parent->l_child = p;
	}
	if (r->is_right_child)
	{
		r->parent->r_child = p;
	}
	r->parent = p;
	r->r_child = nullptr;
	if (p->l_child != nullptr)
	{
		node *q = p->l_child;
		q->is_left_child = false;
		q->is_right_child = true;
		q->parent = r;
		r->r_child = q;
		p->l_child = r;
	}
	else
	{
		p->l_child = r;
	}
	r->is_left_child = true;
	r->is_right_child = false;

	node * q = r;
	while (q != nullptr)
	{
		if (q->r_child == nullptr && q->l_child != nullptr)
		{
			q->height = (q->l_child->height) + 1;
		}
		else if (q->l_child == nullptr && q->r_child != nullptr)
		{
			q->height = (q->r_child->height) + 1;
		}
		else if (q->l_child != nullptr && q->r_child != nullptr)
		{
			q->height = max(q->l_child->height, q->r_child->height) + 1;
		}
		else if (q->l_child == nullptr && q->r_child == nullptr)
		{
			q->height = 1;
		}
		q = q->parent;
	}
}

void avl_tree::R_Rotate(node * p)
{
	node *r = p->parent;
	p->parent = r->parent;
	if (r->parent == nullptr)
	{
		root = p;
		p->is_left_child = r->is_left_child;
		p->is_right_child = r->is_right_child;
	}
	if (r->parent != nullptr)
	{
		p->is_left_child = r->is_left_child;
		p->is_right_child = r->is_right_child;
	}
	if (r->is_left_child)
	{
		r->parent->l_child = p;
	}
	if (r->is_right_child)
	{
		r->parent->r_child = p;
	}
	r->parent = p;
	r->l_child = nullptr;
	if (p->r_child != nullptr)
	{
		node*q = p->r_child;
		q->is_right_child = false;
		q->is_left_child = true;
		q->parent = r;
		r->l_child = q;
		p->r_child = r;
	}
	else
	{
		p->r_child = r;
	}

	r->is_left_child = false;
	r->is_right_child = true;
	node * q = r;
	while (q != nullptr)
	{
		if (q->r_child == nullptr && q->l_child != nullptr)
		{
			q->height = (q->l_child->height) + 1;
		}
		else if (q->l_child == nullptr && q->r_child != nullptr)
		{
			q->height = (q->r_child->height) + 1;
		}
		else if (q->l_child != nullptr && q->r_child != nullptr)
		{
			q->height = max(q->l_child->height, q->r_child->height) + 1;
		}
		else if (q->l_child == nullptr && q->r_child == nullptr)
		{
			q->height = 1;
		}
		q = q->parent;
	}
}
void avl_tree::in_order_traversal(node * p) {
	if (p == nullptr)  return;
	in_order_traversal(p->l_child);
	cout << "value = " << p->value << " " << "height = " << p->height << endl;
	in_order_traversal(p->r_child);
}



int main() {
	//-------------------------for test---------------------
	//avl_tree t1;
	/*t1.add_node(100);
	t1.add_node(50);
	t1.add_node(150);
	t1.add_node(20);
	t1.add_node(60);
	t1.add_node(120);
	t1.add_node(160);
	t1.add_node(55);
	t1.add_node(75);
	t1.in_order_traversal(t1.root);
	cout << endl;
	t1.remove_node(100);*/

	//----------------------------test3-------------------
	/*t1.add_node(100);
	t1.add_node(50);
	t1.add_node(200);
	t1.add_node(30);
	t1.add_node(80);
	t1.add_node(150);
	t1.add_node(300);
	t1.add_node(400);
	t1.add_node(130);
	t1.add_node(150);
	t1.add_node(100);
	t1.add_node(80);
	t1.add_node(20);
	t1.add_node(200);
	t1.in_order_traversal(t1.root);
	cout << endl;
	t1.remove_node(400);
	t1.in_order_traversal(t1.root);
	cout << endl;
	
	t1.remove_node(300);
	t1.in_order_traversal(t1.root);
	cout << endl;*/



	/*t1.add_node(100);
	t1.add_node(90);
	t1.add_node(110);
	t1.add_node(80);
	t1.add_node(95);
	t1.add_node(105);
	t1.add_node(120);
	t1.add_node(70);
	t1.add_node(85);
	t1.add_node(93);
	t1.add_node(98);
	t1.add_node(115);
	t1.add_node(65);
	t1.add_node(75);

	t1.in_order_traversal(t1.root);
	cout << endl;
	t1.remove_node(105);
	t1.in_order_traversal(t1.root);
	cout << endl;*/
	
	//----------------------//
	avl_tree t1;
	t1.add_node(200);
	t1.add_node(100);
	t1.add_node(400);
	t1.add_node(500);
	t1.add_node(300);
	t1.add_node(350);
	t1.add_node(150);
	t1.add_node(430);
	t1.add_node(120);
	t1.add_node(115);
	t1.add_node(150);
	t1.add_node(118);
	t1.in_order_traversal(t1.root);
	cout << endl;
	t1.remove_node(400);
	t1.in_order_traversal(t1.root);
	cout << endl;
	t1.remove_node(500);
	t1.in_order_traversal(t1.root);
	cout << endl;
	getchar();
	getchar();
	return 0;
}
