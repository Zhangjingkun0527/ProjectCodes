import a.*;

public class B{
    public static void main(String args[]){
        var a = new A();
		a.printSomething();
		var c = new C();
    }
	
	static class C{
		public C(){
			System.out.println("this is C");
		}
	}

	class D{
        private void nothing(){
            System.out.println("this is D");
        }
    }
}