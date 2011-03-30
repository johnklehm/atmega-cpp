

#pragma once

namespace atmega{

	template <typename TSIZE = uint16_t>
	struct _stringnode{
	public:
		char *str;
		uint8_t refCount;
		TSIZE length;

		/**
			*	Create a new string node from an existing string
			*
			*	@param astr the string to construct a stringnode from
			*	@param size the number of bytes to copy from astr
			*	@return the newly created string
			*	@note a null character is added to the copied string
			*/
		static _stringnode* create(const char *astr, uint16_t size){
			_stringnode *node = (_stringnode*) malloc(sizeof(_stringnode));
			node->length = size;
			node->refCount = 0;
			node->str = (char*)malloc(size + 1);
			memcpy(node->str,astr,size);
			node->str[size] = '\0';

			return node;
		}

		/**
			*	Destroy an instance of a string node, freeing all memory
			*		associated with it
			*
			*	@param node the stringnode to destroy
			*/
		void decreate(){
			if (this != &nullnode){
				free(this->str);
				free(this);
			}
		}

		/**
			*	Remove a reference to the string node and delete it if
			*		there are no longer any resources associated with it
			*
			*	@param node the stringnode to remove the reference from
			*	@note do not use the stringnode again after calling this
			*		function as the stringnode may no longer exists. 
			*/
		void removeRef(){
			this->refCount--;
			if (this->refCount == 0)
				decreate();
		}


		static _stringnode nullnode;
	};	//end class string::stringnode

}