class ArrayIntegerStack implements IntegerStack{
    private int capacity;
    private int top=0;
    private Integer[] arrStack;
    /*其他代码*/
    /*你的答案，即3个方法的代码*/
    public Integer push(Integer item){
        if(item == null) return null;
        else if(this.size()  >= this.arrStack.length) throw new FullStackException();
        else{
            this.arrStack[top] = item;
            this.top++;
            return item;
        }
    }//如果item为null，则不入栈直接返回null。如果栈满，抛出FullStackException（系统已有的异常类）。
    public Integer pop(){
        if(top == 0) throw new EmptyStackException();
        else if(this.arrStack[top-1] == null) return null;
        else{
            this.top--;
            return this.arrStack[top];
        }
    }//出栈。如果栈空，抛出EmptyStackException，否则返回
    public Integer peek(){
        if(top == 0) throw new EmptyStackException();
        else if(this.arrStack[top-1] == null) return null;
        else return this.arrStack[top];
    }//获得栈顶元素。如果栈空，抛出EmptyStackException。
}
