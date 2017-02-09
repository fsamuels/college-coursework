//: swap.h
// Forrest Samuels 
// 5-5-00
// teaching myself some template useage

template<class TYPE>
void swap(TYPE &x, TYPE &y) {
        TYPE temp = x;
        x = y;
        y = temp;
}


template <class TYPE>
TYPE average(TYPE x, TYPE y) {
	TYPE terms = 2;	//turns out this is not needed
	return (x+y)/terms;
}      

template<class W>
W whoIsBigger(W a, W b) {
	//pre: input 2 things
	//post: returns -1 if same
	//	otherwise returns larger value
     
     if (a == b)
	return -1;
else if (a > b)
	return a;
else
	return b;

}
