import { describe, test, expect } from 'vitest';
import { addUserName } from './solutions';

describe('Problem 09 - addUserName() function', function () {
  test('adds a default name to user messages without a name', function () {
    const chatData = {
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
        },
        {
          role: 'user',
          content: "I'm fine, thanks!",
          name: 'Alice'
        },
        {
          role: 'user',
          content: 'What can you do?'
        }
      ]
    };
    const defaultName = 'Tony';
    addUserName(chatData, defaultName);

    expect(chatData.messages[1].name).toBe(defaultName);
    expect(chatData.messages[3].name).toBe('Alice'); // Should remain unchanged
    expect(chatData.messages[4].name).toBe(defaultName);
  });

  test('does not modify messages that are not from user', function () {
    const chatData = {
      model: 'gpt-4o',
      messages: [
        {
          role: 'assistant',
          content: 'How can I help you today?'
        },
        {
          role: 'user',
          content: 'Hello!'
        }
      ]
    };
    const defaultName = 'Kim';
    addUserName(chatData, defaultName);

    expect(chatData.messages[0].name).toBeUndefined();
    expect(chatData.messages[1].name).toBe(defaultName);
  });
});
