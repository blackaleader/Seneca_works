import { describe, test, expect } from 'vitest';
import { averageForValues } from './solutions';

describe('Problem 4 - averageForValues() function', function () {
  test('averageForValues() returns 0 when no values are passed', () => {
    expect(averageForValues()).toBe(0);
  });

  test('averageForValues() returns the average of a single number', () => {
    expect(averageForValues(10)).toBe(10);
  });

  test('averageForValues() returns the average of multiple numbers', () => {
    expect(averageForValues(10, 20, 30)).toBe(20);
  });

  test('averageForValues() returns the average of a mix of numbers and strings', () => {
    expect(averageForValues(10, '20', 30)).toBe(20);
  });

  test('averageForValues() returns the average of decimal numbers', () => {
    expect(averageForValues(10.5, 20.5, 30.5)).toBe(20.5);
  });

  test('averageForValues() returns the average of decimal numbers as strings', () => {
    expect(averageForValues('10.5', '20.5', '30.5')).toBe(20.5);
  });

  test('averageForValues() returns the average of mixed numbers and strings with decimals', () => {
    expect(averageForValues(10.5, '20.5', 30.5)).toBe(20.5);
  });
});
