#pragma once

#define MAX_TOKENS_IN_MESSAGE 5
#define PJON_MESSAGE_TOKEN_SEPARATOR ";"

/**
 * Pjon message in format type;token[0];token[1];token[n]
 * e.g. VALUES;7327;2296;545874
 * e.g. PING;140
 * e.g. STATE;ON
 */
class PjonMessage {
public:
  static PjonMessage fromString(const char* stringMessage);
  ~PjonMessage();
  const char* getType();
  const char** getValues();
  const char* toString();
private:
  PjonMessage(const char** tokens);
  const char** tokens;
  static const char** parse(const char* stringMessage);
};

