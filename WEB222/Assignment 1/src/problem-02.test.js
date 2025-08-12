import { describe, test, expect } from 'vitest';
import { withTax } from './solutions';

describe('Problem 2 - withTax() function', function () {
  test('calculates the amount with sales tax added for Alberta', () => {
    expect(withTax(1.0, 'AB')).toBeCloseTo(1.05);
  });

  test('calculates the amount with sales tax added for British Columbia', () => {
    expect(withTax(1.0, 'BC')).toBeCloseTo(1.12);
  });

  test('calculates the amount with sales tax added for Manitoba', () => {
    expect(withTax(1.0, 'MB')).toBeCloseTo(1.12);
  });

  test('calculates the amount with sales tax added for New Brunswick', () => {
    expect(withTax(1.0, 'NB')).toBeCloseTo(1.15);
  });

  test('calculates the amount with sales tax added for Newfoundland and Labrador', () => {
    expect(withTax(1.0, 'NL')).toBeCloseTo(1.15);
  });

  test('calculates the amount with sales tax added for Northwest Territories', () => {
    expect(withTax(1.0, 'NT')).toBeCloseTo(1.05);
  });

  test('calculates the amount with sales tax added for Nova Scotia', () => {
    expect(withTax(1.0, 'NS')).toBeCloseTo(1.15);
  });

  test('calculates the amount with sales tax added for Nunavut', () => {
    expect(withTax(1.0, 'NU')).toBeCloseTo(1.05);
  });

  test('calculates the amount with sales tax added for Ontario', () => {
    expect(withTax(1.0, 'ON')).toBeCloseTo(1.13);
  });

  test('calculates the amount with sales tax added for Prince Edward Island', () => {
    expect(withTax(1.0, 'PE')).toBeCloseTo(1.15);
  });

  test('calculates the amount with sales tax added for Quebec', () => {
    expect(withTax(1.0, 'QC')).toBeCloseTo(1.15);
  });

  test('calculates the amount with sales tax added for Saskatchewan', () => {
    expect(withTax(1.0, 'SK')).toBeCloseTo(1.11);
  });

  test('calculates the amount with sales tax added for Yukon', () => {
    expect(withTax(1.0, 'YT')).toBeCloseTo(1.05);
  });
});
