import { describe, test, expect } from 'vitest';
import { isSuccess } from './solutions';

describe('Problem 1 - isSuccess() function', function () {
  test('returns true when status code is successful', function () {
    expect(isSuccess(200)).toBe(true);
    expect(isSuccess(201)).toBe(true);
    expect(isSuccess(226)).toBe(true);
    expect(isSuccess(299)).toBe(true);
  });

  test('returns false when status code is not successful', function () {
    expect(isSuccess(100)).toBe(false);
    expect(isSuccess(199)).toBe(false);
    expect(isSuccess(300)).toBe(false);
    expect(isSuccess(400)).toBe(false);
    expect(isSuccess(500)).toBe(false);
  });
});
