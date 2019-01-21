#include "../includes/ft_ls.h"

/*
 * MergeSort(headRef)
 * 1) If head is NULL or there is only one element in the Linked List 
 *     then return.
 * 2) Else divide the linked list into two halves.  
 *           FrontBackSplit(head, &a, &b);
 * 3) Sort the two halves a and b.
 *     MergeSort(a);
 *     MergeSort(b);
 * 4) Merge the sorted a and b (using SortedMerge() discussed here) 
 *	   and update the head pointer using headRef.
 *	  *headRef = SortedMerge(a, b);
*/

void	split_list(t_lst *source, t_lst **front, t_lst **back)
{
	t_lst	*fast;
	t_lst	*slow;

	slow = source;
	fast = source->next;
	// fast advances two nodes on each iteration, thus finishing the list double the time of slow, and therefore will stop when slow it's at half the list
	while (fast)
	{
		fast = fast->next;
		if (fast)
		{
			slow = slow->next;
			fast = fast->next;
		}
	}
	*front = source;
	*back = slow->next;
	slow->next = NULL;
}

t_lst	*sort_and_merge(t_lst *a, t_lst *b)
{
	t_lst *result;

	result = NULL;
	if (!a)
		return (b);
	else if (!b)
		return (a);

	if (a->data <= b->data)
	{
		result = a;
		result->next = sort_and_merge(a->next, b);
	}
	else
	{
		result = b;
		result->next = sort_and_merge(a, b->next);
	}
	return (result);
}

t_lst *sort_and_merge_ascii(t_lst *a, t_lst *b)
{
	t_lst *result;

	result = NULL;
	if (!a)
		return (b);
	else if (!b)
		return (a);

	if (a->data <= b->data && ft_strcmp(a->content, b->content) >= 0)
	{
		result = a;
		result->next = sort_and_merge(a->next, b);
	}
	else
	{
		result = b;
		result->next = sort_and_merge(a, b->next);
	}
	return (result);
}

void	merge_sort(t_lst **headRef, int func)
{
	t_lst *head;
	t_lst *a;
	t_lst *b;

	head = *headRef;
	if (head == NULL || head->next == NULL)
	{
		return ;
	}

	// split into two sublists
	split_list(head, &a, &b);

	// recursively sort the sublists
	merge_sort(&a, func);
	merge_sort(&b, func);

	// merge the two sorted lists togheter
	if (func == 0)
		*headRef = sort_and_merge(a, b);
	else if (func == 1)
		*headRef = sort_and_merge_ascii(a, b);
}

