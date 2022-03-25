using System;

namespace Compiler.CodeAnalysis.Binding
{
    internal sealed class BoundBinaryExpression : BoundExpression
    {
        public BoundBinaryExpression(BoundExpression left, BoundBinaryOperatorKind operatorKind, BoundExpression operand)
        {
            Left = left;
            OperatorKind = operatorKind;
            Operand = operand;
        }

        public override BoundNodeKind Kind => BoundNodeKind.UnaryExpression;
        public override Type Type => Operand.Type;

        public BoundExpression Left { get; }
        public BoundExpression Right { get; }
        public BoundBinaryOperatorKind OperatorKind { get; }
        public BoundExpression Operand { get; }
    }
}
