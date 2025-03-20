#ifndef LOG_H
#define LOG_H

#include <stdio.h>
#include <stdarg.h>
#include <time.h>

// Niveaux de log
typedef enum {
    LOG_TRACE,   // Trace des événements
    LOG_DEBUG,   // Infos de débogage
    LOG_INFO,    // Infos générales
    LOG_WARN,    // Avertissements
    LOG_ERROR,   // Erreurs
    LOG_FATAL    // Erreurs fatales
} LogLevel;

// Infos d'un événement de log
typedef struct {
    const char *fmt;      // Format du message
    const char *file;     // Nom du fichier
    int line;             // Numéro de ligne
    LogLevel level;       // Niveau de log
    va_list ap;           // Liste d'arguments pour le message formaté
    struct tm *time;      // Heure
} logEvent;

// Variable externe pour stocker le niveau de log courant
extern LogLevel current_log_level;

// Macros pour simplifier l'appel des fonctions de log
#define log_trace(...) log_log(LOG_TRACE, __FILE__, __LINE__, __VA_ARGS__)
#define log_debug(...) log_log(LOG_DEBUG, __FILE__, __LINE__, __VA_ARGS__)
#define log_info(...)  log_log(LOG_INFO,  __FILE__, __LINE__, __VA_ARGS__)
#define log_warn(...)  log_log(LOG_WARN,  __FILE__, __LINE__, __VA_ARGS__)
#define log_error(...) log_log(LOG_ERROR, __FILE__, __LINE__, __VA_ARGS__)
#define log_fatal(...) log_log(LOG_FATAL, __FILE__, __LINE__, __VA_ARGS__)

// Fonction pour définir le niveau de log
void log_set_level(LogLevel level);

// Fonction principale de log
void log_log(LogLevel level, const char *file, int line, const char *fmt, ...);

#endif // LOG_H
