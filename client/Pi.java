package client;

import compute.Task;
import java.util.Formatter;
import java.io.Serializable;

public class Pi implements Task<String>, Serializable {

    private static final long serialVersionUID = 227L;

    /** digits of precision after the decimal point */
    private final int opcao, id, nota;    
    /**
     * Construct a task to calculate pi to the specified
     * precision.
     */
    public Pi(int opcao, int id, int nota) {
        this.opcao = opcao;
        this.id = id;
        this.nota = nota;
    }

    /**
     * Calculate pi.
     */
    public String execute() {
        return computePi(opcao, id, nota);
    }

    public static String computePi(int opcao, int id, int nota) {
        long start = System.nanoTime();
        /* Processar pedido aqui */
        String resultado = new String();
        long end = System.nanoTime();
        resultado = resultado + String.format("SERVERTIME\t%.6f", (end-start)/1000000000F);
        return resultado;
    }
}
