using System;

namespace GameObject
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("Hello World!");
        }
    }

    class Client
    {

        public static void Main()
        {

            Die d1 = new Die(),
                d2 = new Die(10),
                d3 = new Die(18);

            Card c1 = new Card(Card.CardSuite.spades, Card.CardValue.queen),
                 c2 = new Card(Card.CardSuite.clubs, Card.CardValue.four),
                 c3 = new Card(Card.CardSuite.diamonds, Card.CardValue.ace);

            IGameObject[] gameObjects = { d1, d2, d3, c1, c2, c3 };

            foreach (IGameObject gao in gameObjects)
            {
                Console.WriteLine("{0}: {1} {2}",
                                  gao, gao.GameValue, gao.Medium);
            }
        }
    }


    public enum GameObjectMedium { Paper, Plastic, Electronic }

    public interface IGameObject
    {

        int GameValue
        {
            get;
        }

        GameObjectMedium Medium
        {
            get;
        }
    }

    public class Die : IGameObject
    {
        private int numberOfEyes;
        private Random randomNumberSupplier;
        private readonly int maxNumberOfEyes;

        public Die() : this(6) { }

        public Die(int maxNumberOfEyes)
        {
            randomNumberSupplier =
              new Random(unchecked((int)DateTime.Now.Ticks));
            this.maxNumberOfEyes = maxNumberOfEyes;
            numberOfEyes = NewTossHowManyEyes();
        }

        public void Toss()
        {
            numberOfEyes = NewTossHowManyEyes();
        }

        private int NewTossHowManyEyes()
        {
            return randomNumberSupplier.Next(1, maxNumberOfEyes + 1);
        }

        public int NumberOfEyes()
        {
            return numberOfEyes;
        }

        public override String ToString()
        {
            return String.Format("Die[{0}]: {1}", maxNumberOfEyes, numberOfEyes);
        }

        public int GameValue
        {
            get
            {
                return numberOfEyes;
            }
        }

        public GameObjectMedium Medium
        {
            get
            {
                return
                 GameObjectMedium.Plastic;
            }
        }
    }

    public class Card : IGameObject
    {
        public enum CardSuite { spades, hearts, clubs, diamonds };
        public enum CardValue
        {
            two = 2, three = 3, four = 4, five = 5,
            six = 6, seven = 7, eight = 8, nine = 9,
            ten = 10, jack = 11, queen = 12, king = 13,
            ace = 14
        };

        private CardSuite suite;
        private CardValue value;

        public Card(CardSuite suite, CardValue value)
        {
            this.suite = suite;
            this.value = value;
        }

        public CardSuite Suite
        {
            get { return this.suite; }
        }

        public CardValue Value
        {
            get { return this.value; }
        }

        public override String ToString()
        {
            return String.Format("Suite:{0}, Value:{1}", suite, value);
        }

        public int GameValue
        {
            get { return (int)(this.value); }
        }

        public GameObjectMedium Medium
        {
            get
            {
                return GameObjectMedium.Paper;
            }
        }
    }

}
