#ifndef LAB_0_CONTENT_H
#define LAB_0_CONTENT_H

#endif //LAB_0_CONTENT_H

// Estructura de actividades
typedef struct{
    char type;      // Monumento, Gastronomía, Hospedaje, Deporte, Transporte, Otros
    char location;  // Ubicación
    char schedule;  // Horarios
    double price;   // Precio
    int stars;      // Valoración (0-5)
    char review;    // Reseña, Opiniones, Comentarios
} Activity;