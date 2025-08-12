import { describe, test, expect } from 'vitest';
import { long } from './solutions';

describe('Problem 3 - long() function', function () {
  test('returns "long" when no count is provided', () => {
    expect(long()).toBe('long');
  });

  test('returns "long" when count is 0', () => {
    expect(long(0)).toBe('long');
  });

  test('returns "long" when count is 1', () => {
    expect(long(1)).toBe('long');
  });

  test('returns "loong" when count is 2', () => {
    expect(long(2)).toBe('loong');
  });

  test('returns "looooong" when count is 5', () => {
    expect(long(5)).toBe('looooong');
  });
});
