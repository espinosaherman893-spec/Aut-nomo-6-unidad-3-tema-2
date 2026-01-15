/*
 UNIVERSIDAD NACIONAL DE CHIMBORAZO
 FACULTAD DE INGENIERÍA

 Carrera: Ciencia de Datos
 Nombre: Herman Alberto Espinosa Jiménez
 Asignatura: Programación
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <string>
#include <limits> // para numeric_limits

using namespace std;

// --- PROTOTIPOS DE FUNCIONES ---
// Utilidad para validar entradas numéricas dentro de un rango
int leerEntero(string mensaje, int min, int max);
void mostrarEncabezado();
void pausar();

// Funciones de Gestión (CRUD y Ordenamiento)
void mostrarDatos(const vector<int>& p, const vector<int>& m, const vector<int>& c);
void ingresarDatos(vector<int>& p, vector<int>& m, vector<int>& c);
void insertarRegistro(vector<int>& p, vector<int>& m, vector<int>& c);
void modificarRegistro(vector<int>& p, vector<int>& m, vector<int>& c);
void buscarRegistro(const vector<int>& p, const vector<int>& m, const vector<int>& c);
void ordenarRegistros(vector<int>& p, vector<int>& m, vector<int>& c);
void eliminarRegistro(vector<int>& p, vector<int>& m, vector<int>& c);

// Funciones de Análisis y Estadística
void analisisEstadistico(const vector<int>& datos, string nombre);
void analisisPersonalizado(const vector<int>& p, const vector<int>& m, const vector<int>& c);
double calcularMedia(const vector<int>& datos);
double calcularMediana(vector<int> datos);
int calcularModa(const vector<int>& datos);

int main() {
    // Declaración de los 3 arreglos paralelos (Vectores)
    vector<int> pasos;
    vector<int> minutos;
    vector<int> calorias; // Tercer arreglo propuesto (Calorías quemadas)
    int op;

    do {
        mostrarEncabezado();
        cout << "\n=== MENU PRINCIPAL ===\n";
        cout << "1. Ingresar datos (al final)\n";
        cout << "2. Insertar registro (en posicion especifica)\n";
        cout << "3. Modificar registro\n";
        cout << "4. Buscar registro\n";
        cout << "5. Mostrar todos los registros\n";
        cout << "6. Ordenar registros\n";
        cout << "7. Eliminar registro\n";
        cout << "8. Estadisticas (Media, Mediana, Moda)\n";
        cout << "9. Analisis Extra (Personalizado)\n";
        cout << "0. Salir\n";

        op = leerEntero("Opcion: ", 0, 9);

        // Switch para manejar la navegación del menú interactivo
        switch (op) {
            case 1: ingresarDatos(pasos, minutos, calorias); break;
            case 2: insertarRegistro(pasos, minutos, calorias); break;
            case 3: modificarRegistro(pasos, minutos, calorias); break;
            case 4: buscarRegistro(pasos, minutos, calorias); break;
            case 5: mostrarDatos(pasos, minutos, calorias); break;
            case 6: ordenarRegistros(pasos, minutos, calorias); break;
            case 7: eliminarRegistro(pasos, minutos, calorias); break;
            case 8:
                if(pasos.empty()) cout << "Lista vacia.\n";
                else {
                    // Se reutiliza la función para cada arreglo individualmente
                    analisisEstadistico(pasos, "Pasos");
                    analisisEstadistico(minutos, "Minutos");
                    analisisEstadistico(calorias, "Calorias");
                }
                break;
            case 9: analisisPersonalizado(pasos, minutos, calorias); break;
            case 0: cout << "Saliendo del sistema...\n"; break;
        }
        if (op != 0) pausar();

    } while (op != 0);

    return 0;
}

// IMPLEMENTACIÓN DE FUNCIONES

// Lee un entero y valida que esté entre min y max. Si falla, pide de nuevo.
int leerEntero(string mensaje, int min, int max) {
    int valor;
    while (true) {
        cout << mensaje;
        if (cin >> valor) {
            if (valor >= min && valor <= max) {
                // Dejar el '\n' en el buffer para que pausar lo consuma de forma controlada
                return valor;
            }
            cout << "Dato fuera de rango. Intente de nuevo (" << min << "-" << max << "): ";
        } else {
            cout << "Dato invalido. Intente de nuevo (" << min << "-" << max << "): ";
            cin.clear(); // Limpia el estado de error de cin
        }
        // Descarta la línea completa para evitar bucles infinitos
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

void mostrarEncabezado() {
    // Limpia pantalla (compatible con Windows y Unix)
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
    cout << " SISTEMA DE SEGUIMIENTO DE ACTIVIDAD FISICA\n";
    cout << "-------------------------------------------\n";
}

void pausar() {
    cout << "\nPresione [Enter] para continuar...";
    // Limpiamos hasta el fin de línea y luego esperamos la pulsación
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

// Agrega un nuevo registro al final de los vectores (push_back)
void ingresarDatos(vector<int>& p, vector<int>& m, vector<int>& c) {
    cout << "\n--- NUEVO REGISTRO ---\n";
    p.push_back(leerEntero("Pasos (0-100000): ", 0, 100000));
    m.push_back(leerEntero("Minutos (0-1440): ", 0, 1440));
    c.push_back(leerEntero("Calorias (0-10000): ", 0, 10000));
    cout << "Datos guardados exitosamente.\n";
}

// Inserta datos en una posición específica desplazando los demás elementos
void insertarRegistro(vector<int>& p, vector<int>& m, vector<int>& c) {
    if (p.empty()) {
        cout << "La lista esta vacia, se agregara al inicio.\n";
        ingresarDatos(p, m, c);
        return;
    }

    int pos = leerEntero("Posicion donde insertar (0-" + to_string(p.size()) + "): ", 0, static_cast<int>(p.size()));

    // insert() requiere un iterador, por eso sumamos pos a begin()
    p.insert(p.begin() + pos, leerEntero("Pasos: ", 0, 100000));
    m.insert(m.begin() + pos, leerEntero("Minutos: ", 0, 1440));
    c.insert(c.begin() + pos, leerEntero("Calorias: ", 0, 10000));
    cout << "Registro insertado correctamente.\n";
}

void modificarRegistro(vector<int>& p, vector<int>& m, vector<int>& c) {
    if (p.empty()) { cout << "No hay registros para modificar.\n"; return; }
    mostrarDatos(p, m, c);

    int i = leerEntero("Seleccione el Indice a editar: ", 0, static_cast<int>(p.size())-1);

    cout << "Editando registro del indice " << i << ":\n";
    // Acceso directo por índice para modificar
    p[i] = leerEntero("Nuevos Pasos: ", 0, 100000);
    m[i] = leerEntero("Nuevos Minutos: ", 0, 1440);
    c[i] = leerEntero("Nuevas Calorias: ", 0, 10000);
    cout << "Registro actualizado.\n";
}

void buscarRegistro(const vector<int>& p, const vector<int>& m, const vector<int>& c) {
    if (p.empty()) { cout << "Lista vacia.\n"; return; }

    cout << "Buscar por: 1.Pasos 2.Minutos 3.Calorias\n";
    int op = leerEntero("Opcion: ", 1, 3);
    // Ajusto límite máximo razonable según el campo que busque
    int maxBuscar = 100000;
    if (op == 2) maxBuscar = 1440;
    else if (op == 3) maxBuscar = 10000;
    int busco = leerEntero("Valor a buscar: ", 0, maxBuscar);
    bool encontrado = false;

    // Recorrido lineal para encontrar coincidencias
    for (size_t i = 0; i < p.size(); i++) {
        bool match = false;
        if (op == 1 && p[i] == busco) match = true;
        else if (op == 2 && m[i] == busco) match = true;
        else if (op == 3 && c[i] == busco) match = true;

        if (match) {
            cout << "-> Encontrado en indice [" << i << "]: "
                 << "Pasos:" << p[i] << " Min:" << m[i] << " Cal:" << c[i] << endl;
            encontrado = true;
        }
    }
    if (!encontrado) cout << "No se encontro ningun registro con ese valor.\n";
}

// Algoritmo de ordenamiento (Burbuja) aplicado a los 3 vectores simultáneamente
void ordenarRegistros(vector<int>& p, vector<int>& m, vector<int>& c) {
    if (p.empty()) return;

    cout << "Criterio de ordenacion: 1.Pasos 2.Minutos 3.Calorias\n";
    int crit = leerEntero("Opcion: ", 1, 3);
    cout << "Tipo: 1.Ascendente 2.Descendente\n";
    int tipo = leerEntero("Opcion: ", 1, 2);

    // Bubble Sort: Compara elementos adyacentes y los intercambia si están en orden incorrecto
    for (size_t i = 0; i + 1 < p.size(); i++) {
        for (size_t j = 0; j + i + 1 < p.size(); j++) {
            bool cambio = false;
            int v1, v2;

            // Determinar qué vector se usa para la comparación
            if (crit == 1) { v1 = p[j]; v2 = p[j+1]; }
            else if (crit == 2) { v1 = m[j]; v2 = m[j+1]; }
            else { v1 = c[j]; v2 = c[j+1]; }

            // Determinar si se debe intercambiar según ascendente o descendente
            if ((tipo == 1 && v1 > v2) || (tipo == 2 && v1 < v2)) cambio = true;

            if (cambio) {
                // IMPORTANTE: Si se intercambia en uno, se intercambia en TODOS
                // para mantener la integridad de los datos paralelos.
                swap(p[j], p[j+1]);
                swap(m[j], m[j+1]);
                swap(c[j], c[j+1]);
            }
        }
    }
    cout << "Registros ordenados correctamente.\n";
    mostrarDatos(p, m, c);
}

void eliminarRegistro(vector<int>& p, vector<int>& m, vector<int>& c) {
    if (p.empty()) { cout << "Lista vacia.\n"; return; }

    cout << "1.Eliminar por Posicion  2.Eliminar por Condicion (Pasos < X)\n";
    int op = leerEntero("Opcion: ", 1, 2);

    if (op == 1) {
        int pos = leerEntero("Posicion a eliminar: ", 0, static_cast<int>(p.size())-1);
        // erase() elimina el elemento y reajusta el tamaño del vector
        p.erase(p.begin() + pos);
        m.erase(m.begin() + pos);
        c.erase(c.begin() + pos);
        cout << "Registro eliminado.\n";
    } else {
        int limite = leerEntero("Eliminar todos los dias con PASOS menores a: ", 0, 100000);
        int eliminados = 0;

        // Recorremos el vector HACIA ATRÁS (de final a inicio).
        for (int i = static_cast<int>(p.size()) - 1; i >= 0; --i) {
            if (p[i] < limite) {
                p.erase(p.begin() + i);
                m.erase(m.begin() + i);
                c.erase(c.begin() + i);
                eliminados++;
            }
        }
        cout << "Se eliminaron " << eliminados << " registros que cumplian la condicion.\n";
    }
}

void mostrarDatos(const vector<int>& p, const vector<int>& m, const vector<int>& c) {
    if (p.empty()) { cout << "Tabla vacia.\n"; return; }
    cout << "\nIdx |   Pasos   | Minutos | Calorias\n";
    cout << "------------------------------------\n";
    for (size_t i = 0; i < p.size(); ++i) {
        cout << " " << i << "  | " << p[i] << "  |   " << m[i] << "   |   " << c[i] << "\n";
    }
}

// FUNCIONES ESTADÍSTICAS

double calcularMedia(const vector<int>& datos) {
    if (datos.empty()) return 0;
    double suma = 0;
    for(int valor : datos) suma += valor; // Bucle for-each
    return suma / datos.size();
}

double calcularMediana(vector<int> datos) {
    if (datos.empty()) return 0;
    // Creamos una copia local (datos se pasa por valor) para ordenar sin afectar al original
    sort(datos.begin(), datos.end());
    int n = static_cast<int>(datos.size());
    if (n % 2 == 0) return (datos[n/2 - 1] + datos[n/2]) / 2.0;
    else return datos[n/2];
}

int calcularModa(const vector<int>& datos) {
    if (datos.empty()) return 0;
    int moda = datos[0];
    int maxRepeticiones = 0;

    // Doble bucle para contar frecuencias
    for (size_t i = 0; i < datos.size(); i++) {
        int cuenta = 0;
        for (size_t j = 0; j < datos.size(); j++) {
            if (datos[j] == datos[i]) cuenta++;
        }
        if (cuenta > maxRepeticiones) {
            maxRepeticiones = cuenta;
            moda = datos[i];
        }
    }
    return moda;
}

void analisisEstadistico(const vector<int>& datos, string nombre) {
    cout << "\n--- Estadisticas de " << nombre << " ---\n";
    cout << "Media (Promedio): " << calcularMedia(datos) << endl;
    cout << "Mediana (Valor central): " << calcularMediana(datos) << endl;
    cout << "Moda (Mas frecuente): " << calcularModa(datos) << endl;
}

// Análisis propuesto: Calcula eficiencia (pasos/min) y cuenta días de alta intensidad
void analisisPersonalizado(const vector<int>& p, const vector<int>& m, const vector<int>& c) {
    if (p.empty()) { cout << "No hay datos para analizar.\n"; return; }

    double sumaEficiencia = 0;
    int diasIntensos = 0;
    double totalMinutos = 0;
    int countEficiencia = 0;

    for (size_t i = 0; i < p.size(); i++) {
        // Evitar división por cero
        if (m[i] > 0) {
            sumaEficiencia += static_cast<double>(p[i]) / m[i];
            countEficiencia++;
        }

        // Condición personalizada: más de 300 calorías es un día intenso
        if (c[i] > 300) diasIntensos++;

        totalMinutos += m[i];
    }

    double cadenciaProm = (countEficiencia > 0) ? (sumaEficiencia / countEficiencia) : 0.0;

    cout << "\n--- ANALISIS PERSONALIZADO DE SALUD ---\n";
    cout << "1. Cadencia Promedio (Pasos por minuto): " << cadenciaProm << "\n";
    cout << "   (Indica la velocidad promedio de caminata)\n";
    cout << "2. Tiempo total de ejercicio acumulado: " << (totalMinutos / 60.0) << " horas\n";
    cout << "3. Dias de Alta Intensidad (>300 cal quemadas): " << diasIntensos << endl;
}
