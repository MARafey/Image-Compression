# Image Compression

## This code performs the following tasks:

1. It reads an image and converts it into a grayscale image.
2. The grayscale image is stored in a 2D vector.
3. The 2D vector is converted into a 2D linked list, where each node represents a region of pixels with the same color.
4. The 2D linked list is used to construct a quad tree data structure.
5. The quad tree is saved to a file for future use.
6. The saved quad tree is loaded from the file.
7. The quad tree is used to reconstruct the original image.
8. The reconstructed image is saved to a file.
9. The percentage similarity between the original image and the reconstructed image is calculated and displayed.

## Explanation in simple words:

* The code takes an image, converts it to grayscale, and stores it in a 2D vector.
* The vector is then converted into a linked list, where each node represents a region of pixels with the same color.
* The linked list is used to build a quad tree, a hierarchical data structure that divides the image into smaller regions.
* The quad tree is saved to a file for future use.
* The saved quad tree is loaded from the file.
* Using the loaded quad tree, the code reconstructs the original image by merging the regions with the same color.
* The reconstructed image is saved to a file.
* Finally, the code calculates the percentage similarity between the original and reconstructed images based on the pixel values and displays the result.

### Vector Class:
The Vector class is a templated class that represents a dynamic array.
It provides functionality to create, manipulate, and access elements in the array.
Functions:
* Vector(): Constructor that initializes an empty vector.
* Vector(int s): Constructor that initializes a vector with a given size and sets all elements to 0.
* Vector(const Vector& obj): Copy constructor that creates a deep copy of another Vector object.
* push_back(T val): Adds an element to the vector. If the vector is full, it dynamically increases its size and copies the existing elements.
* swap(Vector& other): Swaps the contents of two Vector objects.
* T operator[](int i): Overloaded operator for accessing elements of the vector using square brackets.
* ~Vector(): Destructor that cleans up the dynamically allocated memory.

### LinkedListNode Class:
Represents a node in a linked list.
Contains a data element and a pointer to the next node.
Functions:
* LinkedListNode(T val): Constructor that sets the data element of the node.
* T get(): Returns the data element of the node.
* void dis(): Displays the data element of the node.

###  LinkedList Class:
Represents a linked list.
Contains a head and tail pointer.
Provides functions to insert elements and display the list.
Functions:
* LinkedList(): Constructor that initializes an empty linked list.
* insert(T val): Inserts a new element at the end of the list.
* getHead(): Returns the head pointer of the linked list.
* display(): Displays the elements of the linked list.

### TwoDimensional_LinkList Class:
Represents a two-dimensional linked list.
Converts a 2D vector of elements into a linked list.
Provides functions to convert, display, and access elements of the linked list.
Functions:
* convertto2DLL(Vector<Vector<T>> image, int rows, int cols): Converts a 2D vector into a two-dimensional linked list.
* display(): Displays the elements of the two-dimensional linked list.
* getHead(): Returns the head pointer of the two-dimensional linked list.
* getElementAt(int row, int col): Retrieves the element at the specified row and column.
  
### QuadTreeNode Class:
Represents a node in a quad tree.
Contains a color value and pointers to its four children nodes.
  
### QuadTree Class:
Represents a quad tree data structure.
Contains a root node and provides functions to construct and reconstruct the tree.
Functions:
* constructFrom2dLL(TwoDimensional_LinkList<T>& ll, int row_start, int row_end, int col_start, int col_end): Constructs a quad tree from a two-dimensional linked list.
* construct(TwoDimensional_LinkList<T>& ll, int rows, int cols): Constructs a quad tree from a two-dimensional linked list.
* reconstructImage(QuadTreeNode* node, int row_start, int row_end, int col_start, int col_end, Mat& img): Reconstructs an image from the quad tree.
  root: Pointer to the root node of the quad tree.
  
### Other Functions:

1. writeNodeToFile(QuadTreeNode* node, string parent_file_name, string position, int depth, QuadTree<T>& quad_tree): Writes the quad tree node information to a file.
2. writeToFile(string parent_file_name, string position, int depth, QuadTree<T>& quad_tree): Writes the quad tree information to a file.
3. readNodeFromFile(ifstream& file, QuadTree<T>& quad_tree): Reads the quad tree node information from a file.
4. readFromFile(ifstream& file): Reads the quad tree information from a file.
5. encodeImage(Mat& img, int threshold): Encodes an image using a quad tree structure.
6. decodeImage(Mat& img): Decodes an image using a quad tree structure.

  
