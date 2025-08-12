import { describe, test, expect } from 'vitest';
import { isModelSupported } from './solutions';

describe('Problem 04 - isModelSupported() function', function () {
  const supportedModels = [
    { id: 'model-id-0', object: 'model', created: 1686935002, owned_by: 'organization-owner' },
    { id: 'model-id-1', object: 'model', created: 1686935002, owned_by: 'organization-owner' },
    { id: 'model-id-2', object: 'model', created: 1686935002, owned_by: 'openai' }
  ];

  test('returns true when the model is supported', function () {
    const chatCompletion = { model: 'model-id-0', messages: [] };
    expect(isModelSupported(chatCompletion, supportedModels)).toBe(true);
  });

  test('returns false when the model is not supported', function () {
    const chatCompletion = { model: 'model-id-unknown', messages: [] };
    expect(isModelSupported(chatCompletion, supportedModels)).toBe(false);
  });

  test('handles cases with multiple supported models', function () {
    const chatCompletion1 = { model: 'model-id-1', messages: [] };
    const chatCompletion2 = { model: 'model-id-2', messages: [] };
    expect(isModelSupported(chatCompletion1, supportedModels)).toBe(true);
    expect(isModelSupported(chatCompletion2, supportedModels)).toBe(true);
  });
});
