import { describe, test, expect } from 'vitest';
import { buildChatApiUrl } from './solutions';

describe('Problem 01 - buildChatApiUrl() function', function () {
  test('appends /chat/completions to a base URL without trailing slash', function () {
    const baseUrl = 'https://api.openai.com/v1';
    const expectedUrl = 'https://api.openai.com/v1/chat/completions';
    expect(buildChatApiUrl(baseUrl)).toBe(expectedUrl);
  });

  test('appends /chat/completions to a base URL with a single trailing slash', function () {
    const baseUrl = 'https://api.openai.com/v1/';
    const expectedUrl = 'https://api.openai.com/v1/chat/completions';
    expect(buildChatApiUrl(baseUrl)).toBe(expectedUrl);
  });

  test('appends /chat/completions to a base URL with multiple trailing slashes', function () {
    const baseUrl = 'https://api.openai.com/v1//';
    const expectedUrl = 'https://api.openai.com/v1/chat/completions';
    expect(buildChatApiUrl(baseUrl)).toBe(expectedUrl);
  });

  test('appends /chat/completions to a non-standard base URL with a trailing slash', function () {
    const baseUrl = 'https://openrouter.ai/api/v1/';
    const expectedUrl = 'https://openrouter.ai/api/v1/chat/completions';
    expect(buildChatApiUrl(baseUrl)).toBe(expectedUrl);
  });

  test('appends /chat/completions to a localhost base URL without trailing slash', function () {
    const baseUrl = 'http://localhost:3000';
    const expectedUrl = 'http://localhost:3000/chat/completions';
    expect(buildChatApiUrl(baseUrl)).toBe(expectedUrl);
  });

  test('appends /chat/completions to a localhost base URL with multiple trailing slashes', function () {
    const baseUrl = 'http://localhost:3000///';
    const expectedUrl = 'http://localhost:3000/chat/completions';
    expect(buildChatApiUrl(baseUrl)).toBe(expectedUrl);
  });
});
