#include <ostream>
#include "List.h"
#include <exception>

template <typename T> 
class ListArray : public List<T> {

    private:
        // miembros privados

	T* arr; 
	int max;
	int n;
	static const int MINSIZE=2;
	
	void resize(int new_size){
		//redimensionar el array al tamaño especificado, con el objetivo de
		// incrementar su capacidad (si está lleno), o bien para reducirla
		//(si está demasiado vacío)
		
		T* new_array = new T[new_size];
		
		for(int i=0; i<n; i++){
			arr[i]= new_array[i];
		}
		arr = new_array;
		max=new_size;
		delete[] arr;

		if (n == max) {
                        max= max * 2;
                }
                for (int b =max;b > n; --b) {
                         arr[b] = arr[b - 1];
                }


	}




    public:
        // miembros públicos, incluidos los heredados de List<T>
    
	void insert(int pos, T e) override {
        	if (pos < 0 || pos > size()-1) {
            		throw std::out_of_range("Posición fuera de rango");
       		 }
        	arr[pos] = e;
    	}

    	void append(T e) override {
        	insert(max-1, e);
    	}

    	void prepend(T e) override {
        	insert(0, e);
    	}

    	T remove(int pos) override {
        	if (pos < 0 || pos > size()-1) {
        	    	throw std::out_of_range("Posición fuera de rango");
        	}
        	T aux  = arr[pos];
		for(int i=pos+1; i<n-1; i++){
			arr[i]=arr[i-1];
		}	
        	--max;
         return aux;
   	}	

    	T get(int pos) override {
        	 if (pos < 0 || pos > size()-1) {
                        throw std::out_of_range("Posición fuera de rango");
		}
        return arr[pos];
    	}


    	int search(T e) override {
        	for (int i = 0; i < n; ++i) {
        	    if (arr[i] == e) {
                	return i;
            		}
        	}	
        return -1;
    	}

    	int size() override {
        	return n;
    	}

   	 bool empty() override {
        	return n == 0;
    	}



	ListArray(){
		
		 arr= new T[MINSIZE];
		 max = MINSIZE;
		 n = 0;
	};
	
	~ListArray(){
		delete[] arr;
	}


	T& operator[](int pos){
		
		if(pos<0 || pos> size()-1){
			throw std::out_of_range("Error posición no válida");
		}

		return arr[pos];
	}


	friend std::ostream& operator<<(std::ostream &out, const ListArray<T> &list){

		 for (int i = 0; i < list.n; ++i) {
            		out << list.arr[i];
            		if (i < list.n - 1) {
                		out << ", ";
            		}	
        	}

        	return out;
	}



};
