#include "log.h"
#include <stdio.h>
#include <stdarg.h>
#include <time.h>

LogLevel current_log_level = LOG_INFO;  // Niveau de log par défaut

// Niveaux de log
static const char *level_strings[] = {
    "TRACE", "DEBUG", "INFO", "WARN", "ERROR", "FATAL"
};

// Fonction pour configurer le niveau de log
void log_set_level(LogLevel level) {
    current_log_level = level;
}

// Fonction pour afficher les logs
void log_log(LogLevel level, const char *file, int line, const char *fmt, ...) {
    if (level < current_log_level) { // On affiche le log si son niveau est supérieur ou égal au niveau actuel
        return;
    }

    logEvent ev;
    ev.fmt = fmt;
    ev.file = file;
    ev.line = line;
    ev.level = level;

    // Récupération de l'heure actuelle
    time_t t = time(NULL);
    ev.time = localtime(&t);

    // Initialisation de la liste d'arguments
    va_start(ev.ap, fmt);

    // Affichage du log sur la sortie standard
    char time_buf[16];
    strftime(time_buf, sizeof(time_buf), "%H:%M:%S", ev.time);
    fprintf(stderr, "%s %-5s %s:%d: ", time_buf, level_strings[level], ev.file, ev.line);
    vfprintf(stderr, ev.fmt, ev.ap);
    fprintf(stderr, "\n");
    fflush(stderr);

    // Nettoyage de la liste d'arguments
    va_end(ev.ap);

    printf("\n");
}
