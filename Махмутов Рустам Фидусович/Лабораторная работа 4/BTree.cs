using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace BTree
{
    class BTree
    {
        public int Degree { get; set; }
        public BTreeNode Root { get; set; }

        public BTreeNode FindParent(BTreeNode node)
        {
            
            BTreeElement search = null;
            
            BTreeNode tmp = this.Root;
            
            if (node == null || node == this.Root)
                return null;
            
            do
            {
                
                if (tmp.Child == node)
                {
                    return tmp;
                }
                
                search = tmp.Elements.Where(x => x.Child == node).FirstOrDefault();
                if (search != null)
                    return tmp;

                else
                {
                    
                    
                    if (node.Elements.Max(x => x.Key) < tmp.Elements.OrderBy(x => x.Key).First().Key)
                    {
                        tmp = tmp.Child;
                    }
                    else
                    {
                         
                        var elements = tmp.Elements.OrderBy(x => x.Key).ToArray();
                        for (int i = tmp.Elements.Count() - 1; i >= 0; i--)
                        {
                            if (node.Elements.Max(x => x.Key) > elements[i].Key)
                            {
                                tmp = elements[i].Child;
                                break;
                            }
                        }
                    }
                }
            }
            while (!tmp.IsLeaf);
            return tmp;
        }


        
        private void CheckAndSplitNode(BTreeNode tmp)
        {
            
            if (tmp != null && !(tmp.Elements.Count <= this.Degree - 1))
            {
                
                var lst = tmp.Elements.OrderBy(x => x.Key).ToList();
                
                var split = lst[lst.Count / 2];
                
                BTreeNode left = tmp;
                left.Elements.Clear();
                left.Elements.AddRange(lst.Where(x => x.Key < split.Key).ToList());
              
                BTreeNode right = new BTreeNode();
                right.Elements.AddRange(lst.Where(x => x.Key > split.Key).ToList());
                right.Child = split.Child;
                split.Child = right;

                
                BTreeNode parent = null;
                
                if (tmp == this.Root)
                {
                    parent = new BTreeNode();
                    parent.Child = left;
                    this.Root = parent;
                    parent.Elements.Add(split);
                    return;

                }
                else
                {
                   
                    parent = this.FindParent(left);
                }
                parent.Elements.Add(split);
                
                CheckAndSplitNode(parent);

            }
        }

        
        public bool Add(int key, string val)
        {
            string s = "";
            
            if (this.Search(key, ref s))
                return false;
            
            BTreeNode tmp = null;
            
            if (this.Root == null)
            {
                this.Root = new BTreeNode(key, val);
            }
            else
            {
                
                tmp = this.Root;
                
                while (!tmp.IsLeaf)
                {
                    bool found = false;
                    var elements = tmp.Elements.OrderBy(x => x.Key).ToArray();

                    for (int i = tmp.Elements.Count() - 1; i >= 0; i--)
                    {
                        if (key > elements[i].Key)
                        {

                            
                            tmp = elements[i].Child;
                            found = true;
                            break;
                        }
                    }
                    
                    if (!found)
                    {
                        tmp = tmp.Child;
                    }
                }
                
                tmp.AddElement(key, val);
                
                this.CheckAndSplitNode(tmp);

            }
            return true;

        }


        
        public bool Search(int key, ref string f)
        {
            
            var tmp = this.Root;
            BTreeElement el = null;
           
            while (tmp != null)
            {
                el = tmp.Elements.Where(x => x.Key == key).FirstOrDefault();
                if (el != null)
                {
                    f = el.Value;
                    return true;
                }
                var elements = tmp.Elements.OrderBy(x => x.Key).ToArray();
                
                if (key < elements[0].Key)
                {
                    tmp = tmp.Child;
                }
                
                else
                {
                    for (int i = tmp.Elements.Count() - 1; i >= 0; i--)
                    {
                        if (key > elements[i].Key)
                        {

                            tmp = elements[i].Child;
                            break;
                        }
                    }
                }

            }
            
            return false;
        }

        
        public bool Delete(int key, ref BTree newTree)
        {
            string s = "";
            if (Search(key, ref s))
            {
                
                newTree = new BTree();
                newTree.Degree = this.Degree;
                
                Queue<BTreeNode> q = new Queue<BTreeNode>();
                q.Enqueue(this.Root);
                while (q.Count > 0)
                {
                    var item = q.Dequeue();
                    
                    foreach (var elm in item.Elements.Where(x=>x.Key!=key))
                    {
                        newTree.Add(elm.Key, elm.Value);
                    }

                    
                    if (!item.IsLeaf)
                    {
                        q.Enqueue(item.Child);
                        foreach (var elm in item.Elements)
                        {
                            q.Enqueue(elm.Child);
                        }
                    }
                }
                return true;
            }
            return false;
        }
    }


    //класс узел дерева
    class BTreeNode
    {

        public void AddElement(int key, string val)
        {
            this.Elements.Add(new BTreeElement(key, val));
        }
        public BTreeNode() { }
        public BTreeNode(int key, string val)
        {
            this.Elements.Add(new BTreeElement(key, val));
        }
        public string Value { get; set; }
        public List<BTreeElement> Elements = new List<BTreeElement>();
        public BTreeNode Child;

        public bool IsLeaf { get { return this.Child == null && this.Elements.Where(x => x.Child != null).Count() == 0; } }


        //рекурсивный метод для печати содержимого узла (вызывается от корня для печати всего деревап)
        public void Print(string indent, bool last)
        {
            Console.Write(indent);
            if (last)
            {
                Console.Write("\\-");
                indent += "  ";
            }
            else
            {
                Console.Write("|-");
                indent += "| ";
            }
            Console.WriteLine(this.Elements.Aggregate("", (current, next) => current + ", " + next.Key.ToString()));//Name
            this.Child?.Print(indent, 0 == this.Elements?.Count);
            var elements = this.Elements.OrderBy(x => x.Key).ToArray();
            for (int i = 1; i <= this.Elements.Count; i++)
                elements[i - 1].Child?.Print(indent, i == Elements?.Count);
        }

    }


    //класс-элемент узла дерева
    class BTreeElement
    {
        //констурктор
        public BTreeElement(int key, string val, BTreeNode child = null) { this.Key = key; this.Value = val; }
        public int Key { get; set; }
        public string Value { get; set; }

        //ссылка на узел-потомок
        public BTreeNode Child;


    }

}
