#include "maria_config_helpers.h"

void maria_initialize_config(Maria_config *config) {
  strncpy(config->dbhost, "localhost", 1023);
  strncpy(config->dbuser, "root", 1023);
  strncpy(config->dbpass, "", 1023);
  strncpy(config->dbname, "libnss_maria", 1023);
  config->dbport = 3309;

  config->getpwnam[0] = config->getpwuid[0] = config->getpwent[0] = '\0';
  config->getspnam[0] = config->getspent[0] = '\0';
  config->getgrnam[0] = config->getgrid[0] = config->getgrent[0] = '\0';
  config->memsbygid[0] = config->gidsbymem[0] = '\0';
}

void maria_load_string_setting(config_t libconfig_object, char *destination, const char *selector) {
  // is freed by libconfig
  const char *buffer = malloc(1024 * sizeof(char));
  char message[256];

  if(config_lookup_string(&libconfig_object, selector, &buffer) == CONFIG_TRUE) {
    strncpy(destination, buffer, 1023);
  } else {
    sprintf(message, "cannot load setting from selector=%s", selector);
    maria_log(message);
  }
}

void maria_load_int64_setting(config_t libconfig_object, long long *destination, const char *selector) {
  char message[256];

  if(config_lookup_int64(&libconfig_object, selector, destination) == CONFIG_FALSE) {
    sprintf(message, "cannot load setting from selector=%s", selector);
    maria_log(message);
  }
}

int maria_set_config_from_file(const char *path, Maria_config *config) {
  FILE* libconfig_stream = fopen(path, "r");
  char message[256];

  if(libconfig_stream != NULL) {
    config_t libconfig_object;
    config_init(&libconfig_object);

    if(config_read(&libconfig_object, libconfig_stream) == CONFIG_TRUE) {
      maria_load_string_setting(libconfig_object, config->dbhost, "database_settings.host");
      maria_load_string_setting(libconfig_object, config->dbname, "database_settings.database");
      maria_load_string_setting(libconfig_object, config->dbuser, "database_settings.username");
      maria_load_string_setting(libconfig_object, config->dbpass, "database_settings.password");
      maria_load_int64_setting(libconfig_object, &(config->dbport), "database_settings.port");

      maria_load_string_setting(libconfig_object, config->getpwnam, "nss_queries.getpwnam");
      maria_load_string_setting(libconfig_object, config->getpwuid, "nss_queries.getpwuid");
      maria_load_string_setting(libconfig_object, config->getpwent, "nss_queries.getpwent");

      maria_load_string_setting(libconfig_object, config->getspnam, "nss_queries.getspnam");
      maria_load_string_setting(libconfig_object, config->getspent, "nss_queries.getspent");

      maria_load_string_setting(libconfig_object, config->getgrnam, "nss_queries.getgrnam");
      maria_load_string_setting(libconfig_object, config->getgrid, "nss_queries.getgrid");
      maria_load_string_setting(libconfig_object, config->getgrent, "nss_queries.getgrent");

      maria_load_string_setting(libconfig_object, config->memsbygid, "nss_queries.memsbygid");
      maria_load_string_setting(libconfig_object, config->gidsbymem, "nss_queries.gidsbymem");

      config_destroy (&libconfig_object);
      return 0;
    } else {
      sprintf(message, "error found in file %s, message: %s, line: %i",
        path,
        config_error_text(&libconfig_object),
        config_error_line(&libconfig_object)
      );

      maria_log(message);
      config_destroy(&libconfig_object);
      fclose(libconfig_stream);
      return 1;
    }
  } else {
    sprintf(message, "opening file failed, file=%s, error number=%d, error description=%s", path, errno, strerror(errno));
    maria_log(message);
    return 1;
  }

  fclose(libconfig_stream);
}
