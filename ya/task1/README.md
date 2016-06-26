## Problems
 *  In destructior wrong deallocation of memory ( should be "delete [] points;") since points is an array
 *  In function "bool read(FILE* file)" wrong order  of the initialization list. It should be the same as the order of member variable declaration in the class.
	It won't cause the error in this particular case, but since the class members are guaranteed to be initialized in the declaration order,  the order should be the same.
 *  In function "bool read(FILE* file)"  there is a memory leak. Calling the read function twice will cause memory leak.
 *  In function "bool read(FILE* file)" bad error handling. In case of any error inside read function data stored inside the class should become invalid. So, at least type value should become "eUnknown". Overwise program may crash while executing "void draw()" after the failed read function.
 *  In function  "bool read(FILE* file)"  pointer to the file is not checked for NULL value.
 
 
 
