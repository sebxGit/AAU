public class tree {
	node a = new node(null, null, "a");
	node n = new node(null, null, "n");
	node Var1 = new node(a, null, "var");
	node Var2 = new node(n, null, "var");
	node Plus = new node(Var1, Var2, "plus");

	node One = new node(null, null, "1");
	node Int = new node(One, null, "int");
	node Times = new node(Plus, Int, "times");

	node Nodes[] = {a,n,Var1, Var2, Plus, One, Int, Times};
	void showTree(){
		for (node node : Nodes) {
			System.out.printf("\n[State] "+node.value);
		}
	}
}