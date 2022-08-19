// See  for more information
using DS_14;

namespace DS14
{
    class Program
    {
        static void Main()
        {
            Node<int> first = new Node<int>();
            Node<int> current = first;
            for (int i = 0; i < 10; i++)
            {
                current.Value = i;
                if (i < 9)
                {
                    current.Next = new Node<int>();
                }
                current = current.Next;
            }

            current = first;
            for (int i = 0; i < 10; i++)
            {
                Console.WriteLine(current.Value);
                if (i < 9)
                {
                    current = current.Next;
                }
            }

            ReverseLinkedList<int>(first);
            Console.WriteLine();
            Console.WriteLine();
            Console.WriteLine();
            Console.WriteLine();

            
            for (int i = 0; i < 10; i++)
            {
                Console.WriteLine(current.Value);
                current = current.Next;
            }
        }

        //static void ReverseLinkedList<T>(Node<T> current, Node<T> prev = null)
        //{
        //    if (current.Next != null)
        //    {
        //        ReverseLinkedList(current.Next, current);
        //    }

        //    current.Next = prev;
        //}


        static void ReverseLinkedList<T>(Node<T> start)
        {
            
            if (current.Next != null)
            {
                ReverseLinkedList(current.Next, current);
            }

            current.Next = prev;
        }
    }
}