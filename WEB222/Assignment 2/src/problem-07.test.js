import { describe, test, expect } from 'vitest';
import { trimChatMessages } from './solutions';

describe('Problem 07 - trimChatMessages() function', function () {
  test('removes messages from the start when exceeding maxCharacters', function () {
    const chatCompletion = {
      model: 'gpt-4o',
      messages: [
        { role: 'assistant', content: 'How can I help you today?' },
        { role: 'user', content: 'Hello!' },
        { role: 'assistant', content: 'Hello, how are you?' }
      ]
    };
    const maxCharacters = 25; // Only allows for the first message
    trimChatMessages(chatCompletion, maxCharacters, 'start');

    // Expected outcome after trimming
    const expectedMessages = [
      { role: 'user', content: 'Hello!' },
      { role: 'assistant', content: 'Hello, how are you?' }
    ];

    expect(chatCompletion.messages).toEqual(expectedMessages);
  });

  test('removes messages from the end when exceeding maxCharacters', function () {
    const chatCompletion = {
      model: 'gpt-4o',
      messages: [
        { role: 'assistant', content: 'How can I help you today?' },
        { role: 'user', content: 'Hello!' },
        { role: 'assistant', content: 'Hello, how are you?' }
      ]
    };
    const maxCharacters = 31; // Allows for the first and second messages
    trimChatMessages(chatCompletion, maxCharacters, 'end');

    // Expected outcome after trimming
    const expectedMessages = [
      { role: 'assistant', content: 'How can I help you today?' },
      { role: 'user', content: 'Hello!' }
    ];

    expect(chatCompletion.messages).toEqual(expectedMessages);
  });

  test('throws an error if trimming all messages is necessary to meet maxCharacters', function () {
    const chatCompletion = {
      model: 'gpt-4o',
      messages: [
        { role: 'assistant', content: 'How can I help you today?' },
        { role: 'user', content: 'Hello!' },
        { role: 'assistant', content: 'Hello, how are you?' }
      ]
    };
    const maxCharacters = 5; // Not enough for even the shortest message

    expect(() => {
      trimChatMessages(chatCompletion, maxCharacters, 'start');
    }).toThrow(
      'Trimming all messages is necessary to meet the maxCharacters limit, which is not allowed.'
    );
  });
});
