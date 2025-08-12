import { describe, test, expect } from 'vitest';
import { isValidApiKey } from './solutions';

describe('Problem 02 - isValidApiKey() function', function () {
  test('returns true for valid API keys', function () {
    expect(isValidApiKey('API-KEY-1234-ABCD')).toBe(true);
    expect(isValidApiKey('API-KEY-1234-9876')).toBe(true);
    expect(isValidApiKey('API-KEY-1234-A1B2')).toBe(true);
  });

  test('returns false for API keys with incorrect section lengths', function () {
    expect(isValidApiKey('API-KEY-123-ABCD')).toBe(false);
    expect(isValidApiKey('API-KEY-12345-ABCD')).toBe(false);
  });

  test('returns false for API keys missing dashes', function () {
    expect(isValidApiKey('APIKEY-1234-ABCD')).toBe(false);
    expect(isValidApiKey('API-KEY1234-ABCD')).toBe(false);
  });

  test('returns false for API keys with too many characters in the last section', function () {
    expect(isValidApiKey('API-KEY-1234-ABCDE')).toBe(false);
    expect(isValidApiKey('API-KEY-1234-12345')).toBe(false);
  });

  test('returns false for API keys with non-alphanumeric characters in the last section', function () {
    expect(isValidApiKey('API-KEY-1234-AB@D')).toBe(false);
    expect(isValidApiKey('API-KEY-1234-123#')).toBe(false);
  });
});
