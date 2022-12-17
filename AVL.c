#include<stdio.h>
#include<stdlib.h>
 
struct node
{
    int	data;
    struct node *left;
    struct node *right;
    int height;
};

int height(struct node *N)
{
    if (N == NULL)//yapraklar�n �ocuklar� NULL oldu�undan dolay� y�ksekli�e eklemicez.
        return 0;
    return N->height;
}

int max(int a, int b)
{
    return (a > b)? a : b;//A, B'DEN B�Y�KSE A'YI RETURN ED�YORUZ. B, A'DAN B�Y�KSE B'Y� RETURN ED�YORUZ.
}

struct node* newNode(int data)
{
    struct node* agac = (struct node*)malloc(sizeof(struct node));
    agac->data = data;
    agac->left = NULL;
    agac->right = NULL;
    agac->height = 1;
    return(agac);
}

struct node *rightRotate(struct node *y)
{
    struct node *x = y->left;
    struct node *z = x->right;

    x->right = y;
    y->left = z;

    y->height = max(height(y->left),height(y->right)) + 1;
    x->height = max(height(x->left),height(x->right)) + 1;
 
    return x;
}
 

struct node *leftRotate(struct node *x)
{
    struct node *y = x->right;
    struct node *T2 = y->left;
 

    y->left = x;
    x->right = T2;
 
    x->height = max(height(x->left),height(x->right)) + 1;
    y->height = max(height(y->left),height(y->right)) + 1;

    return y;
}

int getBalance(struct node *N)
{
    if (N == NULL)
        return 0;
    return height(N->left)-height(N->right);//hehhheee leftin y�ksekli�inden rightin y�ksekli�ini ��kar�yoruz ve bu sayede AVL a�ac�n�n en kritik k�sm�na geliyoruzz..
}
 
struct node* insert(struct node* dugum, int data)
{
    if (dugum == NULL)
        return(newNode(data));
 
    if (data < dugum->data)
        dugum->left = insert(dugum->left, data);
    else if (data > dugum->data)
        dugum->right = insert(dugum->right, data);
    else //E�ER G�R�LEN SAYI ZATEN A�A�TA VARSA *DATA==DUGUM->DATA* D�REKT H��B�R ��LEM YAPMADAN RETURN ED�YORUM. hehhhee
        return dugum;
 
    dugum->height = 1 + max(height(dugum->left),height(dugum->right)); //BURADA HER VER� G�R���NDE Y�KSEKL��� G�NCELL�YORUM.
 
    int balance = getBalance(dugum);
 
    // Left Left
    if (balance > 1 && data < dugum->left->data)//BALANCE 1'DEN B�Y�KSE YAN� SOL TARAFTA B�R DENGES�ZL�K VAR DEMEK OLUYOR. AYNI ZAMANDA DA DATA K���KSE R�GHTROTATE YAPIYORUZ.
        return rightRotate(dugum);
    // Right Right
    if (balance < -1 && data > dugum->right->data)//BALANCE -1'DEN K���KSE YAN� SA� TARAFTA B�R DENGES�ZL�K DURUMU OLUYOR. AYNI ZAMANDA DATA B�Y�KSE LEFTROTATE YAPIYORUZ.
        return leftRotate(dugum);
    // Left Right
    if (balance > 1 && data > dugum->left->data)//BALANCE 1DEN B�Y�K VE DATA DA B�Y�KSE SOL SA� DURUMU OLUR. BU Y�ZDEN �NCE LEFTROTATE YAPIP SONRA RIGHTROTATE YAPIYORUZ.
    {
        dugum->left = leftRotate(dugum->left);
        return rightRotate(dugum);
    }
    // Right Left
    if (balance < -1 && data<dugum->right->data)//BALANCE -1DEN K���K VE DATA DA K���KSE SA� SOL DURUMU OLUR. �NCE RIGHTROTATE YAPIP SONRA LEFTROTATE YAPIYORUZ.
    {
        dugum->right = rightRotate(dugum->right);
        return leftRotate(dugum);
    }
//BU ��LEMLER HER YEN� VER� G�R���NDE KONTROL ED�L�YOR. HERHANG� B�R DENGES�ZL�K OLU�TU�UNDA 4 DURUMDAN B�R�S�N� GER�EKLE�T�REREK A�ACIMIZIN DENGE DURUMUNU TEKRAR SA�LIYORUZ..
    return dugum;
}
 
void preOrder(struct node *root)
{
    if(root != NULL)
    {
        printf("%d ", root->data);
        preOrder(root->left);
        preOrder(root->right);
    }
}

int main()
{
  struct node *root = NULL;
 
  root = insert(root, 10);
  root = insert(root, 20);
  root = insert(root, 30);
  root = insert(root, 40);
  root = insert(root, 50);
  root = insert(root, 25);
 
  /* B�yle olmas� gerekiyor
            30
           /  \
         20   40
        /  \     \
       10  25    50
  */

  printf("AVL Agacimiz Preorder : \n");
  preOrder(root);//30-20-10-25-40-50...
  
 
  return 0;
}
