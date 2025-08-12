import { describe, test, expect } from 'vitest';
import { getMessages } from './solutions';

describe('Problem 05 - getMessages() function', function () {
  const chatCompletion = {
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

  test('returns user messages only', function () {
    const expected = [{ role: 'user', content: 'Hello!' }];
    expect(getMessages(chatCompletion, 'user')).toEqual(expected);
  });

  test('returns assistant messages only', function () {
    const expected = [
      { role: 'assistant', content: 'How can I help you today?' },
      { role: 'assistant', content: 'Hello, how are you?' }
    ];
    expect(getMessages(chatCompletion, 'assistant')).toEqual(expected);
  });

  test('throws an error for invalid roles', function () {
    const invalidRole = 'not user or assistant';
    expect(() => getMessages(chatCompletion, invalidRole)).toThrow(Error);
  });
});
