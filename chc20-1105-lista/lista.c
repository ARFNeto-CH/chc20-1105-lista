 #include "lista.h"

Node* _inserir_node_antes (void*, Node*);
Node* _inserir_node_depois(void*, Node*);

Lista*      _apagar(Lista* l)
{
    if (l == NULL) return NULL;
    printf("Apagando '%s'\n", l->nome);
    free(l->nome);
    if (l->quantos == 0)
    {
        free(l);
        return NULL; // vazia
    };  // if()
    // tem alguma coisa
    Node* node = l->inicio;
    do
    {
        Node* p = node->proxima; // salva esse ponteiro
        free(node);
        node = p;
    } while (node != NULL);
    return NULL;
};  // apagar()

Lista*      _criar(const char* nome)
{
    Lista* nova = (Lista*)malloc(sizeof(Lista));
    nova->nome = (char*)malloc(1 + strlen(nome));
    strcpy(nova->nome, nome);
    nova->quantos = 0;
    nova->maximo = 0;
    nova->inicio = NULL;
    nova->fim = NULL;
    return nova;
};  // criar()

int         _define_maximo(Lista* l, const unsigned m)
{
    if (l == NULL) return -1;
    // o novo valor nao pode diminuir a lista abaixo
    // dos que ja tem la claro
    if (l->quantos > m) return -2;
    l->maximo = m;
    return m;
};  //define_maximo

/*
 aqui a ideia e simples: tenho um elemento 'item'
 para inserir. Mas quero inserir na ordem.
 So que nao sei qual o conteudo entao nao sei qual a ordem.

 Se eu tiver que saber o conteudo entao a lista nao sera mais
 generica e o trabalho nao vai poder ser usado depois sem
 alterar o codigo, compilar e tal

 Logico que nao queremos abrir mao disso porque nao queremos
 mexer mais nesse codigo. Uma lista e uma lista afinal

 A solucao e a simples, usada em todas as bibliotecas e
 sistemas desde os '60. So vai mudando o nome. Hook, CallBack
 sei la

 A funcao f() escrita pelo cara que conhece os items compara dois
 itens e devolve -1, 0 ou 1 conforme o primeiro seja menor
 igual ou maior que o segundo Pronto

Se a funcao veio em branco insere no final e pronto

Queremos manter uma propriedade chamada estabilidade, que ocorre
quando os elementos iguais sao inseridos um depois do outro

*/
Lista*      _inserir_na_ordem(void* item, Lista* l, int(*f)(void*, void*))
{
    if (l == NULL) return l; // sem lista
    if (item == NULL) return l; // sem item
    // se nao veio a funcao insere no fim e pronto
    if (f == NULL)
        return _inserir_no_final(item, l);
    // se nao tinha nada insere no final. Ou no inicio
    if (l->quantos == 0)
        return _inserir_no_final(item, l);
    // entao tem mais gente. o caso comum
    // segue a lista e acha a posicao
    Node* p = l->inicio;
    // agora comparamos os itens
    // p->item e item para inserir, claro, na ordem
    do
    {
        int res = f(item, p->item); // -1,0,1
        // se voltou > 0 a posicao e mais pra frente
        // continua na lista
        if (res > 0)
        {
            p = p->proxima;
            continue;
        };  // if()
        // se voltou 0 insere o item depois de p
        if (res == 0)
            // aqui tem uma pegadinha se for inserir depois do ultimo
            if (p == l->fim)
                l->fim = _inserir_node_depois(item, p);
            else
                p = _inserir_node_depois(item, p);
        else
        {
            // aqui tem uma pegadinha se for inserir antes do primeiro
            if (p == l->inicio)
                l->inicio = _inserir_node_antes(item, p);
            else
                p = _inserir_node_antes(item, p);
        };  // if()
        // agora atualiza a quantidade e retorna
        l->quantos = l->quantos + 1;
        return l;
    } while (p != NULL);
    // se nao retornou ainda e porque esse novo item e o maior
    // de todos entao insere no final
    return _inserir_no_final(item, l);
};  // inserir_na_ordem()

Lista*      _inserir_no_inicio(void* item, Lista* l)
{
    if (l == NULL) return l; // sem lista
    if ((l->maximo > 0) && (l->quantos == l->maximo)) return l; // nao cabe
    // cabe: cria um novo node e poe logo no comeco
    Node* novo = (Node*)malloc(sizeof(Node));
    novo->item = (Node*)item; // o dado em si
    novo->anterior = NULL; // vai ser o primeiro
    novo->proxima = l->inicio; // depois vem o que estava na frente
    l->inicio = novo; // novo fim
    l->quantos = l->quantos + 1;
    // se esse e o primeiro inicio = fim = novo
    if (l->quantos == 1)l->fim = novo;
    return l;
};  // inserir_no_inicio()

Lista*      _inserir_no_final(void* item, Lista* l)
{
    if (l == NULL) return l;
    if ((l->maximo > 0) && (l->quantos == l->maximo)) return l; // nao cabe
    // cabe: cria um novo no e poe la no fim
    Node* novo = (Node*)malloc(sizeof(Node));
    novo->item = (Node*)item; // o dado em si
    // se estava vazio entao inicia os ponteiros
    if (l->quantos == 0)
    {
        l->inicio = novo;
        novo->anterior = NULL;
        novo->proxima = NULL;
    }
    else
    {
        novo->anterior = l->fim; // o ultimo de antes
        novo->proxima = NULL; // depois nao tem ninguem
        (l->fim)->proxima = novo;
    };  // if()
    l->fim = novo; // novo fim
    l->quantos = l->quantos + 1;
    // se esse e o primeiro inicio = fim = novo
    if (l->quantos == 1)l->inicio = novo;
    return l;
};  // inserir_no_final()

int         _listar(Lista* l)
{
    if (l == NULL) return -1;
    if (l->maximo > 0)
    {
        printf("\nLista '%s' com %d de %d elementos MAX\n",
            l->nome,
            l->quantos,
            l->maximo
            );
    }
    else
    {
        printf("\nLista '%s' com %d elementos [MAX nao definido]\n",
            l->nome,
            l->quantos
            );
    }
    if (l->quantos < 1) return 0;
    // assume item como um unico int* so pra testar
    Node* p = l->inicio;
    printf("\n    Primeiro: %4d\n", *(int*)(l->inicio->item));
    printf("      Ultimo: %4d\n", *(int*)(l->fim->item));
    printf("\nElementos\n\n");
    do
    {
        printf("%d \n", *(int*)(p->item));
        p = p->proxima;
    } while (p != NULL); 
    printf("\nFim da lista\n\n");
    return 0;
};  // listar()

int         _listar_do_seu_jeito(Lista* l, int(*f)(void*))
{
    if (l == NULL) return -1;
    if (l->maximo > 0)
    {
        printf("\nLista '%s' com %d de %d elementos MAX\n",
            l->nome,
            l->quantos,
            l->maximo
            );
    }
    else
    {
        printf("\nLista '%s' com %d elementos [MAX nao definido]\n",
            l->nome,
            l->quantos
            );
    }
    if (l->quantos < 1) return 0;
    // assume item como um unico int* so pra testar
    Node* p = l->inicio;
    printf("\n    Primeiro: %4d\n", *(int*)(l->inicio->item));
    printf("      Ultimo: %4d\n", *(int*)(l->fim->item));
    printf("\nElementos\n\n");
    do
    {
        f(p->item);
        p = p->proxima;
    } while (p != NULL);
    printf("\nFim da lista\n\n");
    return 0;
};  // listar_do_seu_jeito()

Node*       _primeiro(Lista* l)
{
    if (l == NULL) return NULL;
    return l->inicio;
};  // ultimo()

Lista*      _remover(void* item, Lista* l)
{
    return NULL;
};  // remover()

int         _tamanho(Lista* l)
{
    if (l == NULL) return -1;
    return (int)l->quantos;
};  // tamanho()

Node*       _ultimo(Lista* l)
{
    if (l == NULL) return NULL;
    return l->fim;
};  // ultimo()

int         _vazia(Lista* l)
{   // retorna 1 = true se a lista esta vazia.
    if (l == NULL) return -1;
    return (l->quantos == 0); // sim, so isso
};  // vazia()

// funcoes auxiliares em ordem alfabetica

Node*       _inserir_node_antes(void* item, Node* deste)
{
    // era pra retornar se desse erro no malloc()
    Node* novo = (Node*)malloc(sizeof(Node));
    novo->item = (Node*)item; // o dado em si
    // acerta os ponteiros do novo item
    novo->anterior = (deste)->anterior; // o ultimo de antes
    novo->proxima = (deste); // depois nao tem ninguem
    // inseriu antes entao atualiza 'deste'
    // pode estar inserindo antes do primeiro
    if( deste->anterior != NULL)
        (deste->anterior)->proxima = novo;
    return novo;
};  // inserir_node_antes()

Node*       _inserir_node_depois(void* item, Node* deste)
{
    // era pra retornar se desse erro no malloc()
    Node* novo = (Node*)malloc(sizeof(Node));
    novo->item = (Node*)item; // o dado em si
    // acerta os ponteiros do novo item
    novo->anterior = deste; // o ultimo de antes
    novo->proxima = (deste)->proxima; // depois nao tem ninguem
    // inseri antes entao atualiza 'deste'
    ((deste)->proxima)->anterior = novo;
    return novo;
};  // inserir_node_depois()

// fim de lista.c