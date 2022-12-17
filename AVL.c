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
    if (N == NULL)//yaprakların çocukları NULL olduğundan dolayı yüksekliğe eklemicez.
        return 0;
    return N->height;
}

int max(int a, int b)
{
    return (a > b)? a : b;//A, B'DEN BÜYÜKSE A'YI RETURN EDİYORUZ. B, A'DAN BÜYÜKSE B'Yİ RETURN EDİYORUZ.
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
    struct node *z = y->left;
 

    y->left = x;
    x->right = z;
 
    x->height = max(height(x->left),height(x->right)) + 1;
    y->height = max(height(y->left),height(y->right)) + 1;

    return y;
}

int getBalance(struct node *N)
{
    if (N == NULL)
        return 0;
    return height(N->left)-height(N->right);//leftin yüksekliğinden rightin yüksekliğini çıkarıyoruz ve bu sayede AVL ağacının en kritik kısmına geliyoruzz..
}
 
struct node* insert(struct node* dugum, int data)
{
    if (dugum == NULL)
        return(newNode(data));
 
    if (data < dugum->data)
        dugum->left = insert(dugum->left, data);
    else if (data > dugum->data)
        dugum->right = insert(dugum->right, data);
    else //EĞER GİRİLEN SAYI ZATEN AĞAÇTA VARSA *DATA==DUGUM->DATA* DİREKT HİÇBİR İŞLEM YAPMADAN RETURN EDİYORUM.
        return dugum;
 
    dugum->height = 1 + max(height(dugum->left),height(dugum->right)); //BURADA HER VERİ GİRİŞİNDE YÜKSEKLİĞİ GÜNCELLİYORUM.
 
    int balance = getBalance(dugum);
 
    // Left Left
    if (balance > 1 && data < dugum->left->data)//BALANCE 1'DEN BÜYÜKSE YANİ SOL TARAFTA BİR DENGESİZLİK VAR DEMEK OLUYOR. AYNI ZAMANDA DA DATA KÜÇÜKSE RİGHTROTATE YAPIYORUZ.
        return rightRotate(dugum);
    // Right Right
    if (balance < -1 && data > dugum->right->data)//BALANCE -1'DEN KÜÇÜKSE YANİ SAĞ TARAFTA BİR DENGESİZLİK DURUMU OLUYOR. AYNI ZAMANDA DATA BÜYÜKSE LEFTROTATE YAPIYORUZ.
        return leftRotate(dugum);
    // Left Right
    if (balance > 1 && data > dugum->left->data)//BALANCE 1DEN BÜYÜK VE DATA DA BÜYÜKSE SOL SAĞ DURUMU OLUR. BU YÜZDEN ÖNCE LEFTROTATE YAPIP SONRA RIGHTROTATE YAPIYORUZ.
    {
        dugum->left = leftRotate(dugum->left);
        return rightRotate(dugum);
    }
    // Right Left
    if (balance < -1 && data<dugum->right->data)//BALANCE -1DEN KÜÇÜK VE DATA DA KÜÇÜKSE SAĞ SOL DURUMU OLUR. ÖNCE RIGHTROTATE YAPIP SONRA LEFTROTATE YAPIYORUZ.
    {
        dugum->right = rightRotate(dugum->right);
        return leftRotate(dugum);
    }
//BU İŞLEMLER HER YENİ VERİ GİRİŞİNDE KONTROL EDİLİYOR. HERHANGİ BİR DENGESİZLİK OLUŞTUĞUNDA 4 DURUMDAN BİRİSİNİ GERÇEKLEŞTİREREK AĞACIMIZIN DENGE DURUMUNU TEKRAR SAĞLIYORUZ..
    return dugum;
}

struct node *Delete(struct node *root, int data)
{
	if (root == NULL)
		return NULL;
	if (data > root->data)
		root->right = Delete(root->right, data);
	else if (data < root->data)
		root->left = Delete(root->left, data);

	if (data == root->data)
	{
		struct node *temp = root;	// silinecek öğeyi geçici pointera aktarıyoruz, işlem sonunda free() yapıcaz.
		if (root->left == NULL && root->right == NULL)
		{
			free(root);
			return NULL;
		}
		if (root->left != NULL)						
		{
			struct node *ptr = root->left;					
			if (root->right != NULL)				
			{
				root = root->right;					
				struct node *ptr2 = root;
				while (ptr2->left != NULL)
				ptr2 = ptr2->left;
			
				ptr2->left = ptr;					
				ptr2->height = 1 +max(height(ptr2->left), height(ptr2->right));	// yükseklik ayarını güncelliyorum.
			}
			else	// rootun SAĞ çocuğu NULL ise, SOL çocuğunu root yap.
				root = ptr;
		}
		else	// rootun SOL çocuğu NULL ise, SAĞ çocuğunu root yap.
			root = root->right;
		free(temp);
	}
	if (root == NULL)	//	Veri bulunmadıysa NULL dön.
		return NULL;
	//	YÜKSEKLİK AYARINI GÜNCELLİYORUM
	root->height = 1 + max(height(root->left), height(root->right));
	//	DENGESİZLİK KONTROLÜ
	int balance = getBalance(root);
	//	DURUM KONTROL
	if (balance > 1)
	{
		if (getBalance(root->left) > 0)
			return rightRotate(root);
		else
		{
			root->left = leftRotate(root->left);
			return rightRotate(root);
		}
	}
	else if (balance < -1)
	{
		if (getBalance(root->right) < 0)
			return leftRotate(root);
		else
		{
		root->right = rightRotate(root->right);
		return leftRotate(root);
		}
	}
	return root;
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
 
  /* Böyle olması gerekiyor
            30
           /  \
         20   40
        /  \     \
       10  25    50
  */

  printf("AVL Agacimiz Preorder : \n");
  preOrder(root);//30-20-10-25-40-50...
  
  Delete(root,20);
  printf(" \n AVL Agacimiz Preorder : \n");
  preOrder(root);//30-25-10-40-50...
    /* Böyle olması gerekiyor
            30
           /  \
         25   40
        /       \
       10       50
  */

  Delete(root,40);
  printf(" \n AVL Agacimiz Preorder : \n");
  preOrder(root);//30-25-10-50...
     /* Böyle olması gerekiyor
            30
           /  \
         25   50
        /
       10
  */

  return 0;
}
