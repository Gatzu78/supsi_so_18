//
// Created by Attilio, Antonio, Luciano & Stefano
//

execution_context thread1_ctx;
execution_context thread2_ctx;

void thread1() {
    for (int i = 0; i < 10000; i++) {
        save_context(thread1_ctx);
        restore_context(thread2_ctx);
    }
}

void thread2() {
    for(int i=0; i<10000; i++) {
        // Do some computation
        save_context(thread2_ctx);
        restore_context(thread1_ctx);
    }
}

void main() {
    while(1) {
        thread1();
        thread2();
        break;
    }
}