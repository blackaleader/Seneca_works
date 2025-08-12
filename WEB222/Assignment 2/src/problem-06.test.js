import { describe, test, expect } from 'vitest';
import { countTotalCharacters } from './solutions';

describe('Problem 06 - countTotalCharacters() function', function () {
  test('counts total characters in all messages', function () {
    const chat = {
      model: 'gpt-4o',
      messages: [
        {
          role: 'assistant',
          content: 'How can I help you today?'
        },
        {
          role: 'user',
          content: 'Hello!'
        },
        {
          role: 'assistant',
          content: 'Hello, how are you?'
        }
      ]
    };
    expect(countTotalCharacters(chat)).toBe(50);
  });

  test('returns 0 for empty messages array', function () {
    const chat = {
      model: 'gpt-4o',
      messages: []
    };
    expect(countTotalCharacters(chat)).toBe(0);
  });

  test('handles chat with varying message lengths', function () {
    const chat = {
      model: 'gpt-4o',
      messages: [
        {
          role: 'assistant',
          content: 'Short'
        },
        {
          role: 'user',
          content: 'A very, very long message indeed that goes on and on.'
        }
      ]
    };
    expect(countTotalCharacters(chat)).toBe(58);
  });
});
