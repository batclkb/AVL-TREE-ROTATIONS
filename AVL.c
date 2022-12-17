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
    if (N == NULL)//yapraklarýn çocuklarý NULL olduðundan dolayý yüksekliðe eklemicez.
        return 0;
    return N->height;
}

int max(int a, int b)
{
    return (a > b)? a : b;//A, B'DEN BÜYÜKSE A'YI RETURN EDÝYORUZ. B, A'DAN BÜYÜKSE B'YÝ RETURN EDÝYORUZ.
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
    return height(N->left)-height(N->right);//hehhheee leftin yüksekliðinden rightin yüksekliðini çýkarýyoruz ve bu sayede AVL aðacýnýn en kritik kýsmýna geliyoruzz..
}
 
struct node* insert(struct node* dugum, int data)
{
    if (dugum == NULL)
        return(newNode(data));
 
    if (data < dugum->data)
        dugum->left = insert(dugum->left, data);
    else if (data > dugum->data)
        dugum->right = insert(dugum->right, data);
    else //EÐER GÝRÝLEN SAYI ZATEN AÐAÇTA VARSA *DATA==DUGUM->DATA* DÝREKT HÝÇBÝR ÝÞLEM YAPMADAN RETURN EDÝYORUM. hehhhee
        return dugum;
 
    dugum->height = 1 + max(height(dugum->left),height(dugum->right)); //BURADA HER VERÝ GÝRÝÞÝNDE YÜKSEKLÝÐÝ GÜNCELLÝYORUM.
 
    int balance = getBalance(dugum);
 
    // Left Left
    if (balance > 1 && data < dugum->left->data)//BALANCE 1'DEN BÜYÜKSE YANÝ SOL TARAFTA BÝR DENGESÝZLÝK VAR DEMEK OLUYOR. AYNI ZAMANDA DA DATA KÜÇÜKSE RÝGHTROTATE YAPIYORUZ.
        return rightRotate(dugum);
    // Right Right
    if (balance < -1 && data > dugum->right->data)//BALANCE -1'DEN KÜÇÜKSE YANÝ SAÐ TARAFTA BÝR DENGESÝZLÝK DURUMU OLUYOR. AYNI ZAMANDA DATA BÜYÜKSE LEFTROTATE YAPIYORUZ.
        return leftRotate(dugum);
    // Left Right
    if (balance > 1 && data > dugum->left->data)//BALANCE 1DEN BÜYÜK VE DATA DA BÜYÜKSE SOL SAÐ DURUMU OLUR. BU YÜZDEN ÖNCE LEFTROTATE YAPIP SONRA RIGHTROTATE YAPIYORUZ.
    {
        dugum->left = leftRotate(dugum->left);
        return rightRotate(dugum);
    }
    // Right Left
    if (balance < -1 && data<dugum->right->data)//BALANCE -1DEN KÜÇÜK VE DATA DA KÜÇÜKSE SAÐ SOL DURUMU OLUR. ÖNCE RIGHTROTATE YAPIP SONRA LEFTROTATE YAPIYORUZ.
    {
        dugum->right = rightRotate(dugum->right);
        return leftRotate(dugum);
    }
//BU ÝÞLEMLER HER YENÝ VERÝ GÝRÝÞÝNDE KONTROL EDÝLÝYOR. HERHANGÝ BÝR DENGESÝZLÝK OLUÞTUÐUNDA 4 DURUMDAN BÝRÝSÝNÝ GERÇEKLEÞTÝREREK AÐACIMIZIN DENGE DURUMUNU TEKRAR SAÐLIYORUZ..
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
 
  /* Böyle olmasý gerekiyor
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
