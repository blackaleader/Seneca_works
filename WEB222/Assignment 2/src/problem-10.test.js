import { describe, test, expect } from 'vitest';
import { copySystemPrompts } from './solutions';

describe('Problem 10 - copySystemPrompts() function', function () {
  test('copies system prompts from source to target, replacing existing ones', function () {
    const source = {
      model: 'gpt-4o',
      messages: [{ role: 'system', content: 'New instructions to model...' }]
    };
    const target = {
      model: 'gpt-4o',
      messages: [
        { role: 'system', content: 'Old instructions to model...' },
        { role: 'assistant', content: 'How can I help you today?' },
        { role: 'user', content: 'Hello!' }
      ]
    };
    const expected = {
      model: 'gpt-4o',
      messages: [
        { role: 'system', content: 'New instructions to model...' },
        { role: 'assistant', content: 'How can I help you today?' },
        { role: 'user', content: 'Hello!' }
      ]
    };
    expect(copySystemPrompts(source, target)).toEqual(expected);
  });

  test('adds system prompts to target when none exist', function () {
    const source = {
      model: 'gpt-4o',
      messages: [{ role: 'system', content: 'Initial instructions to model...' }]
    };
    const target = {
      model: 'gpt-4o',
      messages: [
        { role: 'assistant', content: 'How can I help you today?' },
        { role: 'user', content: 'Hello!' }
      ]
    };
    const expected = {
      model: 'gpt-4o',
      messages: [
        { role: 'system', content: 'Initial instructions to model...' },
        { role: 'assistant', content: 'How can I help you today?' },
        { role: 'user', content: 'Hello!' }
      ]
    };
    expect(copySystemPrompts(source, target)).toEqual(expected);
  });

  test('correctly replaces multiple system prompts in target with multiple from source', function () {
    const source = {
      model: 'gpt-4o',
      messages: [
        { role: 'system', content: 'First new instruction to model...' },
        { role: 'system', content: 'Second new instruction to model...' },
        { role: 'system', content: 'Third new instruction to model...' }
      ]
    };
    const target = {
      model: 'gpt-4o',
      messages: [
        { role: 'system', content: 'First old instruction to model...' },
        { role: 'system', content: 'Second old instruction to model...' },
        { role: 'assistant', content: 'How can I help you today?' },
        { role: 'user', content: 'Hello!' }
      ]
    };
    const expected = {
      model: 'gpt-4o',
      messages: [
        { role: 'system', content: 'First new instruction to model...' },
        { role: 'system', content: 'Second new instruction to model...' },
        { role: 'system', content: 'Third new instruction to model...' },
        { role: 'assistant', content: 'How can I help you today?' },
        { role: 'user', content: 'Hello!' }
      ]
    };
    expect(copySystemPrompts(source, target)).toEqual(expected);
  });
});
