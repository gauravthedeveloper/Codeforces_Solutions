import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int n = scanner.nextInt(); 
        int t = scanner.nextInt();

        int[] books = new int[n];
        for (int i = 0; i < n; i++) {
            books[i] = scanner.nextInt();
        }

        int maxBooks = getMaxBooks(n, t, books);
        System.out.println(maxBooks);
        scanner.close();
    }

    public static int getMaxBooks(int n, int t, int[] books) {
        int maxBooks = 0;
        int sum = 0;
        int left = 0;

        for (int right = 0; right < n; right++) {
            sum += books[right];

            while (sum > t) {
                sum -= books[left];
                left++;
            }

            maxBooks = Math.max(maxBooks, right - left + 1);
        }

        return maxBooks;
    }
}