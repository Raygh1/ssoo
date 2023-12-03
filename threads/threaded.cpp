#include <iostream>
#include <opencv2/opencv.hpp>
#include <thread>
#include <vector>

using namespace cv;
using namespace std;
using namespace chrono;

// Función para convertir una parte de imagen a escala de gris
void convertirAGris(const Mat& imagenColor, Mat& imagenGris, int inicioFila, int finFila) {
    for (int r = inicioFila; r < finFila; r++) {
        for (int c = 0; c < imagenColor.cols; c++) {
            Vec3b pixel = imagenColor.at<Vec3b>(r, c);
            uchar valorGris = 0.299 * pixel[2] + 0.587 * pixel[1] + 0.114 * pixel[0];
            imagenGris.at<uchar>(r, c) = valorGris;
        }
    }
}

// Función para divir la imagen en partes y asignar cada parte a un hilo distinto
void convertirAGrisWrapper(const Mat& imagenColor, Mat& imagenGris) {
    vector<thread> hilos;
    int filasPorHilo = imagenColor.rows / numHilos; 

    for (int i = 0; i < numHilos; i++) {
        int inicioFila = i * filasPorHilo;
        int finFila = (i == numHilos - 1) ? imagenColor.rows : (i + 1) * filasPorHilo;

        hilos.emplace_back(convertirAGris, ref(imagenColor), ref(imagenGris), inicioFila, finFila);
    }

    // Espera que todos los hilos finalicen
    for (auto& hilo : hilos) {
        hilo.join();
    }
}

int main(int argc, char* argv[]) {
    // Validacion de argumentos de entrada en input
    if (argc != 4) {
        cerr << "Uso: " << argv[0] << " <imagen_color_entrada> <imagen_gris_salida> <num_hilos>" << endl;
        return EXIT_FAILURE;
    }

    // Definir variables y número de hilos
    string parametroEntrada = argv[1];
    string parametroSalida = argv[2];
    int numHilos = atoi(argv[3]);

    // Funcion para cargar imagen a color
    Mat imagenColor = imread(parametroEntrada, IMREAD_COLOR);

    // Verificar si imagen logró cargarse correctamente
    if (imagenColor.empty()) {
        cerr << "Error: No se pudo leer la imagen de entrada." << endl;
        return EXIT_FAILURE;
    }

    // Imprime por pantalla los valores de filas y columnas
    cout << "Cargando imagen..." << endl;
    cout << "Filas (alto): " << imagenColor.rows << " Columnas (ancho): " << imagenColor.cols << endl;

    // Inicio del tiempo de reloj de conversión
    auto inicio = high_resolution_clock::now();

    // Creación de imagen en escala gris
    Mat imagenGris(imagenColor.rows, imagenColor.cols, CV_8UC1);

    // Llama a función para convertir a escala de gris usando threads
    convertirAGrisWrapper(imagenColor, imagenGris);

    // Tiempo final de reloj de conversión y medición de tiempo
    auto fin = high_resolution_clock::now();
    auto duracion = duration_cast<milliseconds>(fin - inicio);

    // Mensajes de salida por pantalla
    cout << "Inicio de la conversión..." << endl;
    cout << "Fin de la conversión..." << endl;
    cout << "Tiempo total empleado en segundos: " << duracion.count() / 1000.0 << endl;

    // Función para guardar imagen en un nuevo archivo
    imwrite(parametroSalida, imagenGris, {IMWRITE_JPEG_QUALITY, 100});

    // Finaliza la ejecución
    return EXIT_SUCCESS;
}
