#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

void read_kernel_version(char *buffer, size_t buffer_size);
void write_kernel_version_to_html(FILE *f, char *buffer);
void read_uptime(char *buffer, size_t buffer_size);
void write_uptime_to_html(FILE *f, char *buffer);
void read_system_datetime(char *buffer, size_t buffer_size);
void write_system_datetime(FILE *f, char *buffer);
void read_cpuinfo(char *buffer, size_t buffer_size);
void write_cpuinfo_to_html(FILE *f, char *buffer);
void write_html_header(FILE *f);
void write_html_footer(FILE *f);

int main()
{
    FILE *f = fopen("/var/www/t1/index.html", "w");
    flockfile(f);

    write_html_header(f);

    char buffer[256];

    // =========================================

    read_kernel_version(buffer, sizeof(buffer));
    write_kernel_version_to_html(f, buffer);

    // =========================================

    read_uptime(buffer, sizeof(buffer));
    write_uptime_to_html(f, buffer);

    // =========================================

    read_system_datetime(buffer, sizeof(buffer));
    write_system_datetime(f, buffer);

    // =========================================

    read_cpuinfo(buffer, sizeof(buffer));
    write_cpuinfo_to_html(f, buffer);

    // =========================================

    // =========================================

    fclose(f);
    funlockfile(f);

    return 0;
}

void read_kernel_version(char *buffer, size_t buffer_size)
{
    FILE *version_file = fopen("../proc/version", "r");
    flockfile(version_file);

    fread(buffer, 1, buffer_size - 1, version_file);

    buffer[20] = '\0';

    fclose(version_file);
    funlockfile(version_file);
}

void write_kernel_version_to_html(FILE *f, char *buffer)
{
    fprintf(f, "<h2>%s</h2>\n", buffer);
}

void read_uptime(char *buffer, size_t buffer_size)
{
    FILE *uptime_file = fopen("/proc/uptime", "r");
    flockfile(uptime_file);

    size_t lineLength = 0;
    while (lineLength < buffer_size - 1)
    {
        size_t bytesRead = fread(buffer + lineLength, 1, 1, uptime_file);
        if (bytesRead == 0 || buffer[lineLength] == '\n')
        {
            buffer[lineLength] = '\0';
            break;
        }
        lineLength++;
    }

    fclose(uptime_file);
    funlockfile(uptime_file);
}

void write_uptime_to_html(FILE *f, char *buffer)
{
    char *token = strtok(buffer, " ");
    int uptime = atoi(token);

    int days = uptime / 86400;
    int hours = (uptime % 86400) / 3600;
    int minutes = (uptime % 3600) / 60;
    int seconds = uptime % 60;

    fprintf(f, "<p>Uptime: %02dd %02dh %02dm %02ds</p>\n", days, hours, minutes, seconds);

    token = strtok(0, " ");
    int idletime = atoi(token);

    days = idletime / 86400;
    hours = (idletime % 86400) / 3600;
    minutes = (idletime % 3600) / 60;
    seconds = idletime % 60;

    fprintf(f, "<p>Idle time: %02dd %02dh %02dm %02ds</p>\n", days, hours, minutes, seconds);
}

void read_system_datetime(char *buffer, size_t buffer_size)
{
    FILE *stat_file = fopen("../proc/stat", "r");
    flockfile(stat_file);

    for (int i = 0; i < 4; i++)
    {
        while (fgetc(stat_file) != '\n' && !feof(stat_file))
            ;
    }

    size_t lineLength = 0;
    while (lineLength < buffer_size - 1)
    {
        size_t bytesRead = fread(buffer + lineLength, 1, 1, stat_file);
        if (bytesRead == 0 || buffer[lineLength] == '\n')
        {
            buffer[lineLength] = '\0';
            break;
        }
        lineLength++;
    }

    fclose(stat_file);
    funlockfile(stat_file);
}

void write_system_datetime(FILE *f, char *buffer)
{
    char *token = strtok(buffer, " ");
    token = strtok(0, " ");

    long epoch = atol(token);

    time_t raw_time = epoch;
    struct tm *time_info = localtime(&raw_time);

    char date_buffer[80];
    strftime(date_buffer, sizeof(date_buffer), "%d/%m/%Y %H:%M:%S", time_info);

    fprintf(f, "<p>Current Date: %s</p>\n", date_buffer);
}

void read_cpuinfo(char *buffer, size_t buffer_size)
{
    FILE *cpuinfo_file = fopen("../proc/cpuinfo", "r");
    flockfile(cpuinfo_file);

    for (int i = 0; i < 4; i++)
    {
        while (fgetc(cpuinfo_file) != '\n' && !feof(cpuinfo_file))
            ;
    }

    size_t lineLength = 0;
    while (lineLength < buffer_size - 1)
    {
        size_t bytesRead = fread(buffer + lineLength, 1, 1, cpuinfo_file);
        if (bytesRead == 0 || buffer[lineLength] == '\n')
        {
            buffer[lineLength] = '!';
            break;
        }
        lineLength++;
    }

    lineLength++;

    while (fgetc(cpuinfo_file) != '\n' && !feof(cpuinfo_file))
        ;

    while (lineLength < buffer_size - 1)
    {
        size_t bytesRead = fread(buffer + lineLength, 1, 1, cpuinfo_file);
        if (bytesRead == 0 || buffer[lineLength] == '\n')
        {
            buffer[lineLength] = '!';
            break;
        }
        lineLength++;
    }

    lineLength++;

    for (int i = 0; i < 4; i++)
    {
        while (fgetc(cpuinfo_file) != '\n' && !feof(cpuinfo_file))
            ;
    }

    while (lineLength < buffer_size - 1)
    {
        size_t bytesRead = fread(buffer + lineLength, 1, 1, cpuinfo_file);
        if (bytesRead == 0 || buffer[lineLength] == '\n')
        {
            buffer[lineLength] = '\0';
            break;
        }
        lineLength++;
    }

    fclose(cpuinfo_file);
    funlockfile(cpuinfo_file);
}

void write_cpuinfo_to_html(FILE *f, char *buffer)
{
    fprintf(f, "<div>\n");
    fprintf(f, "<h3>CPU Information</h3>\n");

    char *token = strtok(buffer, ":");
    token = strtok(0, "!");

    fprintf(f, "<p>Model: %s</p>\n", token);

    token = strtok(0, ":");
    token = strtok(0, "!");

    fprintf(f, "<p>Frequency: %s MHz</p>\n", token);

    token = strtok(0, ":");
    token = strtok(0, "\0");

    fprintf(f, "<p>Cores: %s</p>\n", token);
}

void write_html_header(FILE *f)
{
    fprintf(f, "<!DOCTYPE html>\n");
    fprintf(f, "<html>\n");
    fprintf(f, "<head>\n");
    fprintf(f, "<title>System Information</title>\n");
    fprintf(f, "</head>\n");
    fprintf(f, "<body>\n");
    fprintf(f, "<h1>System Information</h1>\n");
}

void write_html_footer(FILE *f)
{
    fprintf(f, "</body>\n");
    fprintf(f, "</html>\n");
}
