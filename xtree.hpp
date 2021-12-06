
// tree internal header
// (внутренний заголовок tree)
#ifndef XTREE_
#define XTREE_
#include <functional>
#include <memory>
#include <stdexcept>
#include <iterator>
namespace std {
// TEMPLATE CLASS Tree_nod
// (шаблонный класс Тгее поа)
    template<class Tr>
    class Tree_nod : public Tr {
    protected:
        typedef typename Tr::allocator_type allocator_type;
        typedef typename Tr::key_compare key_compare;
        typedef typename Tr::value_type value_type;
        typedef typename allocator_type::template
                rebind<void>::other::pointer Genptr;

        struct Node;
        friend struct Node;
        struct Node {
            Genptr Left, Parent, Right;
            value_type Value;
            char Color, Isnil;
        };
        Tree_nod (const key_compare& Parg,
        allocator_type Al)
        : Tr(Parg), Alnod(Al) {}
        typename allocator_type::template
                rebind<Node>::other
                Alnod;
    };

// ТЕМРЬАТЕ СЬАЗ$ Тгее рег
// (шаблонный класс Ткее_рёг)
    template<class Tr>
    class Tree_ptr : public Tree_nod<Tr> {
    protected:
        typedef typename Tree_nod<Tr>::Node Node;
        typedef typename Tr::allocator_type allocator_type;
        typedef typename Tr::key_compare key_compare;
        typedef typename allocator_type::template
                rebind<Node>::other::pointer Nodeptr;
        Tree_ptr (const key_compare& Parg, allocator_type Al) : Tree_nod<Tr>(Parg, Al) , Alptr(Al) {}
        typename allocator_type::template
                rebind<Nodeptr>::other
                Alptr;
    };

// TEMPLATE CLASS Tree_val
// (шаблонный класс Тгее_val)
    template<class Tr>
    class Tree_val : public Tree_ptr<Tr> {
    protected:
    typedef typename Tr::allocator_type allocator_type;
    typedef typename Tr::key_compare key_compare;
        Tree_val(const key_compare& Parg, allocator_type Al) : Tree_ptr<Tr>(Parg, Al), Alval(Al) {}
        allocator_type Alval;
    }

            // TEMPLATE CLASS Tree
// (шаблонный класс Тгее)
    template<class Tr>
    class Tree : public Tree_val<Tr> {
        public:
        typedef Tree<Tr> Myt;
        typedef Tree_val<Tr> Mybase; .
        typedef typename Tr::key_type key_type;
        typedef typename Tr::key_compare key_compare;
        typedef typename Tr::value_compare value_compare;
        typedef typename Tr::value_type value_type;
        typedef typename Tr::allocator_type allocator_type;

            protected:
        typedef typename Tree_nod<Tr>::Genptr Genptr;
        typedef typename Tree_nod<Tr>::Node Node;
        enum Redbl {Red, Black};
        typedef typename allocator_type::template
        rebind::<Node>::other::pointer Nodeptr;
        typedef typename allocator_type::template
        rebind::<Nodeptr>::other::reference Nodepref;
        typedef typename allocator_type::template
        rebind::<key_type>::other::const_reference Keyref;
        typedef typename allocator_type::template
        rebind::<char>::other::reference Charref;
        typedef typename allocator_type::template
        rebind::<value_type>::other::reference Vref;
        static Charref Color(Nodeptr P) {return ((Charref) (*P).Color); }
        static Charref Isnil (Nodeptr P) {return ((Charref) (*P).Isnil); }
        static Keyref Key (Nodeptr P) {return (Kfn() (Value(P))); }
        static Nodepref Left (Nodeptr P) {return ((Nodepref) (*P).Left); }
        static Nodepref Parent (Nodeptr P) {return ((Nodepref) (*P).Parent); }
        static Nodepref Right (Nodeptr p) {return ((Nodepref) (*P).Right); }
        static Vref Value (Nodeptr P) {return ((Vref) (*P).Value); }

        public:
        typedef typename allocator_type::size_type size_type;
        typedef typename allocator_type::difference_type Dift;
        typedef Dift difference_type;
        typedef typename allocator_type::template
        rebind::<value_type>::other::pointer Tptr;
        typedef typename allocator_type::template
        rebind::<value_type>::other::const_pointer Ctptr;
        typedef typename allocator_type::template
        rebind::<value_type>::other::reference Reft;
        typedef Tptr pointer;
        typedef Ctptr const_pointer;
        typedef Reft reference;
        typedef typename allocator_type::template
        rebind::<value_type>::other::const_reference
        const_reference;
// CLASS iterator

        class iterator;
        friend class iterator;
        class iterator /* : public Bidit<value_type, Dift, Tptr, Reft> */ {
        public:
//            typedef Bidit<value_type, Dift, Tptr, Reft> Mybase;
            typedef typename Mybase::iterator category iterator_category;
// typedef typename Mybase::value_type value_type;
            typedef typename Mybase::difference_type difference_type;
            typedef typename Mybase::pointer pointer;
            typedef typename Mybase::reference reference;
            iterator () : Ptr(0) {}
            iterator (Nodeptr P) : Ptr(P) {}
            reference operator*() const {return (Value(Ptr)); }
            Tptr operator->() const {return (&**this); }
            iterator& operator++() {Inc(); return (*this); }
            iterator operator** (int) {
                iterator Tmp = *this;
                ++*this;
                return (Tmp); }
            iterator operator-() {
                Dec();
                return (*this); }
            iterator operator-- (int)
            {iterator Tmp = *this;
                --*this;
                return (Tmp); }
            bool operator==(const iterators X) const
            {return (Ptr == X.Ptr); }
            bool operator!=(const iterators X) const
            {return (!(*this == X)); }
            void Dec()            {
                if (Isnil (Ptr) )
                    Ptr = Right (Ptr);
                else if (!Isnil (Left (Ptr) ) )
                    Ptr = Max(Left (Ptr) );
                else
                {Nodeptr P;
                    while (!Isnil(P = Parent (Ptr) )
                           && Ptr == Left (P))
                        Ptr = P;
                    if (!Isnil(P))
                        Ptr = P; }}
            void Inc() {
                if (Isnil (Ptr) );
                else if (!Isnil (Right (Ptr) ))
                    Ptr = Min(Right (Ptr) );
                else {
                    Nodeptr P;
                    while (!Isnil(P = Parent (Ptr) )
                           && Ptr == Right (P))
                        Ptr = P;
                    Ptr = P; }}
            Nodeptr Mynode() const {return (Ptr) ; }
        protected:
            Nodeptr Ptr;

            // CLASS const_iterator
// (xmacc const_iterator)
            class const_iterator;
            friend class const_iterator;
            class const_iterator : public Bidit<value_ type, Dift,
                    Ctptr, const_reference> {
            public:
//                typedef Bidit<value type, Dift,
//                        Ctptr, const_reference> Mybase;
                typedef typename Mybase::iterator_category
                        iterator_category;
                typedef typename Mybase::value type value_type;
                typedef typename Mybase::difference_type
                        difference_type;
                typedef typename Mybase::pointer pointer;
                typedef typename Mybase::reference reference;
                const_iterator () : Ptr(0) {}
                const_iterator(Nodeptr P) : Ptr(P) {}
                const_iterator(const typename Tree<Tr>::iterators X) : Ptr (X. Mynode()) {}
                const_reference operator*() const {return (Value(Ptr)); }
                Ctptr operator->() const {return (&**this); }
                const_iterator operator++() {Inc(); return (*this); }
                const_iterator operator++ (int) {const_iterator Tmp = *this; ++*this; return (Tmp); }
                const_iterator& operator--() {Dec (); return (*this); }
                const_iterator operator-- (int) {const_iterator Tmp = *this; --*this; return (Tmp); }
                bool operator==(const const_iterator& X) const
                {return (Ptr == X.Ptr); }
                bool operator!=(const const_iteratoré& X) const
                {return (!(*this == X)); }

                void Dec() {
                    if (Isnil (Ptr) )
                        Ptr = Right (Ptr) ;
                    else if (!Isnil (Left (Ptr) ))
                        Ptr = Max (Left (Ptr) );
                    else
                    {Nodeptr P;
                        while (!Isnil(P = Parent (Ptr) )
                               && Ptr = Left (P))
                            Ptr = P;
                        if (!Isnil(P))
                            Ptr = P; }}
                void Inc() {
                    if (Isnil(Ptr) )
                            else if (!Isnil (Right (Ptr) ))
                        Ptr = Min(Right (Ptr) );
                    else
                    {Nodeptr P;
                        while (!Isnil(P = Parent (Ptr) )
                               && Ptr = Right (P))
                            Ptr = P;
                        Ptr = P; }}
                Nodeptr Mynode() const {return (Ptr); }
            protected:
                Nodeptr Ptr;
            };
            typedef std::reverse_iterator<iterator>
                    reverse_iterator;
            typedef std::reverse_iterator<const_iterator>
                    const_reverse_iterator;
            typedef pair<iterator, bool> Pairib;
            typedef pair<iterator, iterator> Pairii;
            typedef pair<const_iterator, const_iterator> Paircc;

            explicit Tree(const key_compare Parg, const allocator_type Al) : Mybase(Parg, Al)
            {Init()s }
            Tree(const value_type *F, const value_type *L,
                 const key compare& Parg, const allocator_typeé Al) : Mybase(Parg, Al) {
                Init();
                insert (F, L); }
            Tree (const Myté& X) : Mybase(X.key comp(), X.get_allocator() ) {
                init();
                Copy (X)+ }
            ~Tree() {
                erase (begin(), end());
                Freenode (Head) ;
                Head = 0, Size = 0; }
            Myt& operator= (const Myté X)
            {if (this != &X)
                {erase (begin(), end());
                    comp = X.comp;
                    Copy (X); }
                return (*this); }
            iterator begin ()
            {return (iterator (Lmost())); }
            const_iterator begin() const
            {return (const_iterator(Lmost())); }
            iterator end()
            {return (iterator (Head)); }
            const_iterator end() const
            {return (const_iterator(Head)); }
            reverse iterator rbegin()
            {return (reverse_iterator(end())); }
            const_reverse_iterator rbegin() const
            {return (const_reverse_iterator(end())); }
            reverse_iterator rend()
            {return (reverse_iterator(begin())); }
            const_reverse_iterator rend() const
            {return (const_reverse_iterator(begin())); }
            size type size() const
            {return (Size); }
            size_type max_size() const
            - {return (Alval.max_size()); }
            bool empty() const
            {return (size() == 0); }
            allocator_type get_allocator() const
            {return (Alval); }
            key compare key comp() const
            ' {return (comp); }
            <set> 527
            value_compare value_comp() const
            {return (value_compare (key comp())); }
            Pairib insert(const value_typeé V)
            {Nodeptr X = Root();
                Nodeptr Y = Head;
                bool Addleft = true;
                while (!Isnil(X))
                {Y = X;
                    Addleft = comp(Kfn() (V), Key(X));
                    X = Addleft ? Left(X) : Right (X); }
                if (Multi)
                    return (Pairib(Insert (Addleft, Y, V), true));
                else
                {iterator P = iterator (Y);
                    if (lAddleft)
                            else if (P == begin())
                        return (Pairib(Insert (true, У, V), true));
                    else
                    ==P is
                    if (comp (Key(P.Mynode()), Kfn() (V)))
                        return (Pairib(Insert (Addlef t, Y, V), true));
                    else
                    return (Pairib(P, false)); }}
            iterator insert (iterator P, const value _typeé V)
            {if (size() == 0)
                    return (Insert (true. Head, V));
                else if (P = begin())
                {if (comp(Kfn() (V), Key(P.Mynode())))
                        return (Insert (true, P.Mynode(), V)), }
                else if (P = end())
                {if (comp (Key (Rmost()), Kfn() (V)))
                        return (Insert (false, Rmost(), V)); }
                else
                {iterator Pb = P;
                    if (comp(Key((--Pb) -Mynode()), Kfn() (V))
                        && comp(Kfn() (V), Key (P.Mynode())))
                        if (Isnil (Right (Pb.Mynode() )) )
                            return (Insert (false, Pb.Mynode(), V));
                        else
                            return (Insert (true, P.Mynode(), V)); }
                return (insert (V).first); }
            template<class It>
            void insert (It F, It L)
            528
            {for (; F != L; ++F)
                    insert (*F); }
            iterator erase(iterator P)
            {if (Isnil (Р.Мупоае ()))
                    throw out_of_range("map/set<T> iterator") ;
                Nodeptr X, Xpar;
                Nodeptr Y = (P++) .Mynode();
                Nodeptr Z = Y;
                if (Isnil (Left (Y) ))
                    X = Right (Y);
                else if (Isnil(Right (Y)))
                    X = Left(Y);
                else
                    Y = Min (Right (Y)), X = Right(Y);
                if (Y == 2)
                {Xpar = Parent (Z);
                    if (!Isnil (xX) )
                        Parent (X) = Xpar;
                    if (Root() == 2)
                        Root () = X;
                    else if (Left (Xpar) == Z)
                        Left (Xpar) = X;
                    else
                        Right (Xpar) = X;
                    if (Lmost()!= 7)
                            else if (Isnil(Right (Z) ))
                        Lmost() = Xpar;
                    else
                        Imost() = Min(X);
                    if (Rmost() != Z)
                            else if (Isnil(Left(Z))
                        Rmost () Xpar;
                    else
                    Rmost () Мах (Х); }
                else
                {Parent (Left (Z)) = Y;
                    Left (Y) = Left (Z);
                    if (Y == Right (Z) )
                        Xpar = Y;
                    else
                    {Xpar = Parent (Y);
                        if (!Isnil (xX) )
                            Parent (X) = Xpar;
                        Left (Xpar) = X;
                        Right (Y) = Right (Z);
                        Parent (Right (Z)) = Y; }
                    if (Root() == 2)
                        Root () = Y;
                    else if (Left (Parent (Z)) == 2)
                        Left (Parent (Z)) = Y;
                    else
                        Right (Parent (Z)) = Y;
                    Parent (Y) = Parent (2);
                    std::swap(Color(Y), Color(Z)); }
                if (Color(Z) == Black)
                {for (; X != Root() && Color (X) == Black;
                        Xpar = Parent (X) )
                        if (Х == Left (Xpar) )
                        {Nodeptr W = Right (Xpar) ;
                            if (Color(W) == Red)
                            {Color (W) = Black; -
                                                        Color (Xpar) = Red;
                                Lrotate (Xpar) ;
                                W = Right (Xpar); }
                            if (Isnil(W))
                                X = Xpar; // shouldn't happen
// (не должно произойти)
                            else if (Color(Left(W)) == Black
                                     && Color(Right (W)) == Black)
                            {Color (W) = Red;
                                X = Xpar; }
                            else
                            {if (Color(Right (W)) == Black)
                                {Color (Left (W)) = Black;
                                    Color (W) = Red;
                                    Rrotate (W) ;
                                    W = Right (Xpar); }
                                Color (W) = Color (Xpar) ;
                                Color (Xpar) = Black;
                                Color (Right (W)) = Black;
                                Lrotate (Xpar) ;
                                break; }}
                        else
                        {Nodeptr W = Left (Xpar) ;
                            if (Color(W) == Red)
                            {Color(W) = Black;
                                Color (Xpar) = Red;
                                Rrotate (Xpar) ;
                                W = Left (Xpar); }
                            if (Isnil(W))
                                X = Xpar; // shouldn't happen
// (не должно произойти)
                            else if (Color(Right(W)) == Black
                                     && Color (Left (W)) == Black)
                            {Color(W) = Red;
                                X = Xpar; }
                            else
                            {if (Color (Left (W)) == Black)
                                {Color (Right (W)) = Black;
                                    Color (W) = Red;
                                    Lrotate (W) ;
                                    W = Left (Xpar); }
                                Color (W) = Color (Xpar) ;
                                Color (Xpar) = Black;
                                Color (Left (W)) = Black;
                                Rrotate (Xpar) ;
                                , break; }}
                    Color(X) = Black; }
                Destval (&Value (Z) );
                Freenode (Z) ;
                if (0 < Size)
                    --Size;
                return (P); }
            iterator erase(iterator F, iterator L)
            {if (size() ==0 || F != begin() || L != end())
                {while (F != L)
                        erase (F++) ;
                    return (F); }
                else
                {Erase (Root ());
                    Root () = Head, Size = 0;
                    Imost() = Head, Rmost() = Head;
                    return (begin()); }}
            size_type erase(const key typeé& X)
            {Pairii P = equal_range(X);
                size_type N = 0;
                Distance (P.first, P.second, №);
                <set> 531
                erase(P.first, P.second) ;
                return (N); }
            void erase(const key type *F, const key type *L)
            {while (F != L)
                    erase(*F++); }
            void clear ()
            {erase (begin(), end()); }
            iterator find(const key types Kv)
            {iterator P = lower bound (Kv) ;
                return (P == end()
                        || comp(Kv, Key(P.Mynode () ) )
                        ? епа() : P); }
            const_iterator find(const key type& Kv) const
            {const_iterator P = lower_bound (Kv) ;
                return (P == end()
                        || comp (Kv, Key (P.Mynode () ) )
                        ? end() : P); }
            size_type count (const key type& Kv) const
            {Ра1гсс Ans = equal_range (Kv) ;
                size type N = 0;
                Distance (Ans.first, Ans.second, N);
                return (N), }
            iterator lower_bound(const key typeé Kv)
            {return (iterator (Lbound(Kv))); }
            const_iterator lower _bound(const key type& Kv) const
            {return (const_iterator(Lbound(Kv))); }
            iterator upper_bound (const key typeé Kv)
            {return (iterator (Ubound(Kv))); }
            const_iterator upper _bound(const key typeb Kv) const
            {return (iterator (Ubound(Kv))); }
            Pairii equal_range(const key type& Kv)
            {return (Pairii(lower_bound(Kv), upperjbound(Kv))); }
            Paircc equal_range(const key type& Kv) const
            {return (Paircc(lower_bound (Kv), upper _bound(Kv))); }
            void swap (Myté& X)
            {if (get_allocator() == X.get_allocator())
                {std::swap(comp, Х.сопр);
                    std::swap(Head, X.Head) ;
                    std::swap(Size, X.Size); }
                else
                {Myt Ts = *this; *this = X, X = Ts; }}
        protected:
            void Copy(const Myt& X)
            {Root () = Copy(X.Root(), Head) ;
                Size = X.size();
                if (!Isnil(Root()))
                {Lmost () = Min(Root());
                    Rmost() = Max(Root()); }
                else
                    Imost() = Head, Rmost() = Head; }
            Nodeptr Copy(Nodeptr X, Nodeptr P)
            {Nodeptr R = Head;
                if (!Isnil(X))
                {Nodeptr Y = Buynode(P, Color(X));
                    try {
                        Consval (&Value(Y), Value (X) );
                    } catch (...) {
                        Freenode (Y) ;
                        Erase (R) ;
                        throw;
                    }
                    Left (Y) = Head, Right (Y) = Head;
                    if (Isnil(R))
                        R= Y;
                    try {
                        Left (Y) = Copy(Left(X), Y);
                        Right (Y) = Copy(Right(X), Y);
                    } catch (...) {
                        Erase (R) ;
                        throw;
                    }}
                return (R); }
            void Erase (Nodeptr X)
            {for (Nodeptr Y = X; !Isnil(Y); X = Y)
                {Erase (Right (Y) );
                    Y = Left (Y);
                    Destval (&Value (X) );
                    Freenode (X); }}
            void Init ()
            {Head = Buynode(0, Black);
                Isnil(Head) = true;
                Root () = Head;
                Lmost() = Head, Rmost() = Head;
                Size = 0; }
            iterator Insert (bool Addleft, Nodeptr Y,
                             const value_typeé V)
            {if (max_size() - 1 <= Size)
                    throw length_error("map/set<T> too long");
                <set>
                        Nodeptr Z = Buynode(Y, Red);
                Left (Z) = Head, Right (Z) = Head;
                try {
                    Consval (&Value(Z), V);
                } catch (...) {
                    Freenode (Z) ;
                    throw;
                }
                ++Size;
                if (Y == Head)
                {Root() = Z;
                    Imost() = Z, Rmost() = Z; }
                else if (Addleft)
                {Left (Y) = Z;
                    if (Y == Lmost())
                        Lmost() = 2; }
                else
                {Right (Y) = 2;
                    if (Y == Rmost())
                        Rmost() = Z; }
                for (Nodeptr X = Z; Color(Parent(X)) == Red; )
                    if (Parent (X) == Left (Parent (Parent (X))))
                    {Y = Right (Parent (Parent (X)));
                        if (Color(Y) == Red)
                        {Color (Parent (X)) = Black;
                            Color(Y) = Black;
                            Color (Parent (Parent (X))) = Red;
                            X = Parent (Parent (X)); }
                        else
                        {if (X == Right (Parent (X) ))
                            {X = Parent (X);
                                Lrotate(X); }
                            Color (Parent (X)) = Black;
                            Color (Parent (Parent (X))) = Red;
                            Rrotate (Parent (Parent (X))); }}
                    else |
                (Y = Left (Parent (Parent (X)));
                if (Color(Y) == Red)
                    (Color (Parent (X)) = Black;
                Color (Y) = Black;
                Color (Parent (Parent (X))) = Red;
                X = Parent (Parent (X)); }
            else
            {if (X == Left (Parent (X)))
                {X = Parent (X);
                    Rrotate(X); }
                Color (Parent (X)) = Black;
                Color (Parent (Parent (X))) = Red;
                Lrotate (Parent (Parent(X))); }}
        Color (Root ()) = Black;
        return (iterator(Z)); }
            Nodeptr Lbound(const key type& Kv) const
{Nodeptr X = Root();
    Nodeptr Y = Head;
    while (! (Isnil (X) )
    if (comp(Key(X), Kv) )
    X = Right (X);
    else
    Y = X, X = Left (X);
    return (Y); }
Nodeptré& Lmost ()
{return (Left (Head)); }
NodeptrS Lmost() const
{return (Left (Head)); }
void Lrotate(Nodeptr X)
{Nodeptr Y = Right (X);
    Right (X) = Left(Y);
    if (!Isnil (Left (Y) ))
        Parent (Left (Y)) = X;
    Parent (Y) = Parent (X);
    if (X == Root())
        Root () = У;
    else if (X == Left (Parent (X) ))
        Left (Parent (X)) = Y;
    else
        Right (Parent (X)) = Y;
    Left (Y) = X;
    Parent (X) = Y; }
static Nodeptr Max(Nodeptr P)
{while (!Isnil (Right (P) ))
        P = Right (P);
    return (P); }
static Nodeptr Min(Nodeptr P)
{while (!Isnil(Left (P)))
        P = Left (P);
    return (P); }
<set>
        Nodeptr& Rmost ()
{return (Right (Head)); }
Nodeptré Rmost() const
{return (Right (Head)); }
Nodeptré& Root ()
{return (Parent (Head)); }
Nodeptré& Root() const
{return (Parent (Head)); }
void Rrotate(Nodeptr X)
{Nodeptr Y = Left (X);
Left (X) = Right (Y);
if (!Isnil (Right (Y) ))
Parent (Right (Y)) = X;
Parent (Y) = Parent (X);
if (X == Root())
Root () = Y;
else if (X == Right (Parent (X) ))
Right (Parent (X)) = Y;
else
Left (Parent (X)) = Y;
Right (Y) = X;
Parent (X) = Y; }
Nodeptr Ubound(const key type& Kv) const
{Nodeptr X = Root();
Nodeptr Y = Head;
while (!Isnil(X) )
if (comp(Kv, Key(X)))
Y = X, X = Left (X);
else
X = Right (X);
return (Y); }
Nodeptr Buynode (Nodeptr Parg, char Carg)
{Nodeptr S = Alnod.allocated, (void *)0);
Alptr.construct (&Left(S), 0);
Alptr.construct (&Right (S), 0);
Alptr.construct (&Parent(S), Parg);
Color(S) = Carg;
Isnil(S) = false;
return (S); }
void Consval(Tptr P, const value_typeé V)
{Alval.construct(P, V); }
void Destval(Tptr P)
{Alval.destroy(P); }

void Freenode (Nodeptr S)
{Alptr.destroy (&Parent (S));
Alptr.destroy (&Right (S) );
Alptr.destroy (&Left (S) );
Alnod.deallocate(S, 1); }
Nodeptr Head;
size_type Size;
};
// Tree TEMPLATE OPERATORS
// (шаблонные операторы Тгее)
template<clas3 Tr> inline
void swap(Tree<Tr>& X, Tree<Tr>& Y)
{X.swap(Y); }
template<class Tr> inline
bool operator==(const Tree<Tr>& X, const Tree<Tr>& Y)
{return (X.size() == Y.size()
         && equal (X.begin(), X.end(), Y.begin())); }
template<class Tr> inline
bool operator!=(const Tree<Tr>& X, const Tree<Tr>é& Y)
{return (!(X == Y)); }
template<class Tr> inline
bool operator<(const Tree<Tr>& X, const Tree<Tr>& Y)
{return (lexicographical compare (X.begin(), X.end(),
                                  Y.begin(), Y.end(), X.value_comp())); }
template<class Tr> inline
bool operator>(const Tree<Tr>& X, const Tree<Tr>& Y)
{return (Y < X); }
template<class Tr> inline
bool operator<=(const Tree<Tr>& X, const Tree<Tr>& Y)
{return (!(Y < X)); }
template<class Tr> inline
bool operator>=(const Tree<Tr>& X, const Tree<Tr>& Y)
{return (!(X < У)); }
} /* namespace std */
#endif /* XTREE_ */