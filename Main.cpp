#include <opencv2/opencv.hpp>
using namespace cv;
#include <iostream>
#include<fstream>
using namespace std;


template <typename T>
class Vector
{
public:
     Vector()
     {
          counter = 0;
          size = 0;
          arr = new T[size];
     }
     Vector(int s)
     {
          counter = 0;
          size = s;
          arr = new T[size];
          for (int i = 0; i < size; i++)
          {
               arr[i] = 0;
          }
     }
     Vector(const Vector& obj)
     {
          counter = obj.counter;
          size = obj.size;
          arr = new T[size];
          for (int i = 0; i < size; i++)
          {
               arr[i] = obj.arr[i];
          }
     }
     void push_back(T val)
     {
          if (counter < size)
          {
               arr[counter] = val;
               counter++;
          }
          else
          {
               Vector<T> copy(size + 1);
               for (int i = 0; i < size; i++)
               {
                    copy.push_back(arr[i]);
               }
               copy.push_back(val);
               swap(copy);
          }
     }
     void swap(Vector& other)
     {
          std::swap(size, other.size);
          std::swap(counter, other.counter);
          std::swap(arr, other.arr);
     }
     T operator[](int i)
     {
          if (i < counter)
          {
               return arr[i];
          }
          else
          {
               cout << "Out of Range" << endl;
               return INT_MIN;
          }
     }
     ~Vector()
     {
          //delete[] arr;
     }

private:
     int size;
     int counter;
     T* arr;
};

template <typename T>
class LinkedListNode {
public:
     T data;
     LinkedListNode* next;
     LinkedListNode(T val) { data = val; next = nullptr; }
     T get() { return data; }
     void dis() { cout << data << " "; }
};

template <typename T>
class LinkedList {
public:
     LinkedList() { head = nullptr; tail = nullptr; }
     void insert(T val) {
          LinkedListNode<T>* new_node = new LinkedListNode<T>(val);
          if (head == nullptr) {
               head = new_node;
               tail = new_node;
          }
          else {
               tail->next = new_node;
               tail = new_node;
          }
     }
     LinkedListNode<T>* getHead()
     {
          return head;
     }
     void display() {
          LinkedListNode<T>* current = head;
          while (current != nullptr) {
               current->dis();
               current = current->next;
          }
          cout << endl;
     }

private:
     LinkedListNode<T>* head;
     LinkedListNode<T>* tail;
};

template <typename T>
class TwoDimensional_LinkList
{
public:
     void convertto2DLL(Vector<Vector<T>> image, int rows, int cols)
     {
          int start = -1;
          int end = -1;
          int color = 0;
          for (int i = 0; i < rows; i++)
          {
               LinkedList<int> temp;
               for (int j = 0; j < cols; j++)
               {
                    start = j;
                    if (image[i][j] == 255)
                    {
                         color = 255;
                    }
                    else
                    {
                         color = 0;
                    }
                    while (j < cols)
                    {
                         if (image[i][j] == color)
                              j++;
                         else
                              break;
                    }
                    temp.insert(start);
                    temp.insert(j - 1);
                    if (color == 255)
                         temp.insert(-1);
                    else
                         temp.insert(-2);
                    if (j != cols)
                         j = j - 1;

               }
               obj.insert(temp);
          }
     }
     void display() {
          LinkedListNode<LinkedList<T>>* currentOuter = obj.getHead();
          while (currentOuter != nullptr) {
               LinkedList<T> innerList = currentOuter->get();
               LinkedListNode<T>* currentInner = innerList.getHead();
               while (currentInner != nullptr) {
                    currentInner->dis();
                    currentInner = currentInner->next;
               }
               cout << endl;
               currentOuter = currentOuter->next;
          }
     }
     LinkedList<LinkedList<T>> getHead()
     {
          return obj;
     }
     T getElementAt(int row, int col) {
          LinkedList<LinkedList<T>>& list = obj;
          LinkedListNode<LinkedList<T>>* currentRow = list.getHead();
          for (int i = 0; i < row && currentRow != nullptr; ++i) {
               currentRow = currentRow->next;
          }

          LinkedList<T> innerList = currentRow->get();
          LinkedListNode<T>* currentCol = innerList.getHead();
          while (currentCol != nullptr) {
               int start = currentCol->get();
               currentCol = currentCol->next;
               int end = currentCol->get();
               currentCol = currentCol->next;
               int color = currentCol->get();
               currentCol = currentCol->next;

               if (col >= start && col <= end) {
                    return color == -1 ? 255 : 0;
               }
          }
          return -1;
     }
private:
     LinkedList<LinkedList<T>> obj;
};

class QuadTreeNode {
public:
     int color;
     QuadTreeNode* topLeft, * topRight, * bottomLeft, * bottomRight;

     QuadTreeNode() : color(-1), topLeft(nullptr), topRight(nullptr), bottomLeft(nullptr), bottomRight(nullptr) {}
};

template <typename T>
class QuadTree {
public:
     QuadTreeNode* root;

     QuadTree() : root(nullptr) {}

     // Function to construct a quad tree from a 2D linked list of pixels
     QuadTreeNode* constructFrom2dLL(TwoDimensional_LinkList<T>& ll, int row_start, int row_end, int col_start, int col_end) {
          if (row_start > row_end || col_start > col_end) { // if the indices are invalid, return null
               return nullptr;
          }

          // get the color of the target pixel and check if all pixels in the subregion have the same color
          int color = ll.getElementAt(row_start, col_start);
          bool uniform_color = true;

          for (int i = row_start; i <= row_end && uniform_color; ++i) {
               for (int j = col_start; j <= col_end; ++j) {
                    if (ll.getElementAt(i, j) != color) {
                         uniform_color = false;
                         break;
                    }
               }
          }

          QuadTreeNode* node = new QuadTreeNode(); // create a new node

          if (uniform_color) { // if all pixels have the same color, set the node's color to the color of the target pixel
               node->color = color;
          }
          else { // if the pixels do not have the same color, recursively construct the quad tree for the subregions
               int row_mid = (row_start + row_end) / 2;
               int col_mid = (col_start + col_end) / 2;
               node->topLeft = constructFrom2dLL(ll, row_start, row_mid, col_start, col_mid);
               node->topRight = constructFrom2dLL(ll, row_start, row_mid, col_mid + 1, col_end);
               node->bottomLeft = constructFrom2dLL(ll, row_mid + 1, row_end, col_start, col_mid);
               node->bottomRight = constructFrom2dLL(ll, row_mid + 1, row_end, col_mid + 1, col_end);
          }

          return node; // return the new node
     }

     void construct(TwoDimensional_LinkList<T>& ll, int rows, int cols) {
          root = constructFrom2dLL(ll, 0, rows - 1, 0, cols - 1);
     }

     void reconstructImage(QuadTreeNode* node, int row_start, int row_end, int col_start, int col_end, Mat& img) {
          if (node == nullptr) {
               return;
          }

          if (node->color != -1) { // If the node has uniform color
               for (int i = row_start; i <= row_end; ++i) {
                    for (int j = col_start; j <= col_end; ++j) {
                         img.at<uchar>(i, j) = node->color;
                    }
               }
          }
          else {
               int row_mid = (row_start + row_end) / 2;
               int col_mid = (col_start + col_end) / 2;

               reconstructImage(node->topLeft, row_start, row_mid, col_start, col_mid, img);
               reconstructImage(node->topRight, row_start, row_mid, col_mid + 1, col_end, img);
               reconstructImage(node->bottomLeft, row_mid + 1, row_end, col_start, col_mid, img);
               reconstructImage(node->bottomRight, row_mid + 1, row_end, col_mid + 1, col_end, img);
          }
     }
};

template <typename T>
void writeNodeToFile(QuadTreeNode* node, string parent_file_name, string position, int depth, QuadTree<T>& quad_tree) {
     if (node == nullptr) {
          return;
     }

     string file_name = "Files/" + parent_file_name + position + "_d" + to_string(depth) + ".txt";
     ofstream file(file_name);


     file << "Color: " << node->color << endl;
     file << "Position: " << position << endl;
     file << "Children:\n";

     string children_positions[] = { "TL", "TR", "BL", "BR" };
     QuadTreeNode* children[] = { node->topLeft, node->topRight, node->bottomLeft, node->bottomRight };

     for (int i = 0; i < 4; ++i) {
          if (children[i] != nullptr) {
               file << children_positions[i] << ": " << parent_file_name + position + children_positions[i] + "_d" + to_string(depth + 1)  + ".txt" << endl;
          }
          else {
               file << children_positions[i] << ": None" << endl;
          }
     }

     file.close();

     writeNodeToFile(node->topLeft, parent_file_name + position, "TL", depth + 1, quad_tree);
     writeNodeToFile(node->topRight, parent_file_name + position, "TR", depth + 1, quad_tree);
     writeNodeToFile(node->bottomLeft, parent_file_name + position, "BL", depth + 1, quad_tree);
     writeNodeToFile(node->bottomRight, parent_file_name + position, "BR", depth + 1, quad_tree);
}

template <typename T>
void saveQuadTree(QuadTree<T>& quad_tree) {
     writeNodeToFile(quad_tree.root, "", "root", 0, quad_tree);
}

template <typename T>
QuadTreeNode* reconstructNodeFromFile(string file_name, QuadTree<T>& quad_tree) {
     ifstream file(file_name);

     if (!file.is_open()) {
          return nullptr;
     }

     QuadTreeNode* node = new QuadTreeNode();

     string line;
     while (getline(file, line)) {
          if (line.find("Color: ") == 0) {
               node->color = stoi(line.substr(7));
          }
          else if (line.find("Children:") == 0) {
               for (int i = 0; i < 4; ++i) {
                    getline(file, line);
                    size_t pos = line.find(": ");
                    string position = line.substr(0, pos);
                    string child_file_name = line.substr(pos + 2);

                    if (child_file_name != "None") {
                         // Add "Files/" to the child file name
                         child_file_name = "Files/" + child_file_name;
                         if (position == "TL") {
                              node->topLeft = reconstructNodeFromFile(child_file_name, quad_tree);
                         }
                         else if (position == "TR") {
                              node->topRight = reconstructNodeFromFile(child_file_name, quad_tree);
                         }
                         else if (position == "BL") {
                              node->bottomLeft = reconstructNodeFromFile(child_file_name, quad_tree);
                         }
                         else if (position == "BR") {
                              node->bottomRight = reconstructNodeFromFile(child_file_name, quad_tree);
                         }
                    }
               }
               break;
          }
     }

     file.close();
     return node;
}


template <typename T>
void loadQuadTree(QuadTree<T>& quad_tree) {
     quad_tree.root = reconstructNodeFromFile("Files/root_d0.txt", quad_tree);
}

void percentage(Mat img1, Mat img2)
{
     float X = 0.0;
     for (int i = 0; i < img1.rows; i++)
     {
          for (int j = 0; j < img1.cols; j++)
          {
               X = img1.at<uchar>(i, j) - pow(img2.at<uchar>(i, j), 2);
          }
     }
     X = X / (img1.rows * img1.cols);

     float ans = 100 * (1 - ((X) / 255));
     cout << "Percentage : " << ans << "%" << endl;
}

int main()
{
     //part 1
     Mat image = imread("t3.bmp");
     int rows = image.rows;
     int cols = image.cols;

     Vector<Vector<int>> imgVector(rows);

     for (int i = 0; i < rows; i++)
     {
          Vector<int> colums(cols);
          for (int j = 0; j < cols; j++)
          {
               Vec3b color = image.at<Vec3b>(i, j);
               int gray = (color[0] + color[1] + color[2]) / 3;
               colums.push_back(gray);
          }
          imgVector.push_back(colums);
     }

     TwoDimensional_LinkList<int> obj;

     obj.convertto2DLL(imgVector, rows, cols);

     QuadTree<int> tree;
     tree.construct(obj, rows, cols);
     saveQuadTree(tree);
     //part 2
     Mat reconstructed_image(rows, cols, CV_8UC1);
     QuadTree<int> retree;
     loadQuadTree(retree);

     // Reconstruct the image from the quad tree
     tree.reconstructImage(retree.root, 0, rows - 1, 0, cols - 1, reconstructed_image);
     //part 3
     // Save the reconstructed image using OpenCV's imwrite function
     imwrite("reconstructed_image.bmp", reconstructed_image);
     waitKey(0);
     percentage(image, reconstructed_image);
     return 0;
}


