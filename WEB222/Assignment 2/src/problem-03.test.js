import { describe, test, expect } from 'vitest';
import { maskApiKey } from './solutions';

describe('Problem 03 - maskApiKey() function', function () {
  test('masks a valid API key correctly', function () {
    const validApiKey = 'API-KEY-1234-AB3D';
    expect(maskApiKey(validApiKey)).toBe('API-KEY-1234-***D');
  });

  test('does not mask an invalid API key', function () {
    const invalidApiKey = 'API-KEY-1234-ABC';
    expect(maskApiKey(invalidApiKey)).toBe(invalidApiKey);
  });
});
