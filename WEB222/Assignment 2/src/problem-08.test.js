import { describe, test, expect } from 'vitest';
import { formatChatCompletionToHTML, formatChatCompletionToHTML2 } from './solutions';

describe('Problem 08 Part 1 - formatChatCompletionToHTML() function', function () {
  test('formats a chat completion object into an HTML string using semantic elements', function () {
    const chatCompletion = {
      model: 'gpt-4o',
      messages: [
        { role: 'assistant', content: 'How can I help you today?' },
        { role: 'user', content: 'Hello!' },
        { role: 'assistant', content: 'Hello, how are you?' }
      ]
    };
    const expectedHtml = `
      <article>
        <header>Model: gpt-4o</header>
        <section class="assistant">Assistant: How can I help you today?</section>
        <section class="user">User: Hello!</section>
        <section class="assistant">Assistant: Hello, how are you?</section>
      </article>
    `;
    expect(formatChatCompletionToHTML(chatCompletion).trim()).toBe(expectedHtml.trim());
  });
});

describe('Problem 08 Part 2 - formatChatCompletionToHTML2() function', function () {
  test('formats a chat completion object into an HTML string using semantic elements', function () {
    const chatCompletion = {
      model: 'gpt-4o',
      messages: [
        { role: 'assistant', content: 'How can I help you today?' },
        { role: 'user', content: 'Hello!' },
        { role: 'assistant', content: 'Hello, how are you?' }
      ]
    };
    const expectedHtml = `
      <article>
        <header>Model: gpt-4o</header>
        <section class="assistant">Assistant: How can I help you today?</section>
        <section class="user">User: Hello!</section>
        <section class="assistant">Assistant: Hello, how are you?</section>
      </article>
    `;
    expect(formatChatCompletionToHTML2(chatCompletion).trim()).toBe(expectedHtml.trim());
  });
});
