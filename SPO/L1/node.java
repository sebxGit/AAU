public class node {
	node left;
	node right;
	String value;

	public node(String a) {
		value = a;
	}

	public node(node leftNode, node rightNode, String valueString) {
		left = leftNode;
		right = rightNode;
		value = valueString;
	}
}
