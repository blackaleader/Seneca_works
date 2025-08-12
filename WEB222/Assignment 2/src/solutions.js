/**
 * WEB222 – Assignment 02
 *
 * I declare that this assignment is my own work in accordance with
 * Seneca Academic Policy. No part of this assignment has been
 * copied manually or electronically from any other source
 * (including web sites) or distributed to other students.
 *
 * Please update the following with your information:
 *
 *      Name: Arman Ataeipour
 *      Student ID: 186554234
 *      Date: 6/12/2025
 *
 * Please see all unit tests in the files problem-01.test.js, problem-02.test.js, etc.
 */

function buildChatApiUrl(baseUrl) {
  return baseUrl.replace(/\/+$|\/+$/g, '').replace(/\/+$/, '') + '/chat/completions';
}

function isValidApiKey(apiKey) {
  const regex = /^API-KEY-\d{4}-[A-Za-z0-9]{4}$/;
  return regex.test(apiKey);
}

function maskApiKey(apiKey) {
  if (!isValidApiKey(apiKey)) return apiKey;
  return apiKey.slice(0, -4) + '***' + apiKey.slice(-1);
}

function isModelSupported(chatCompletion, supportedModels) {
  return supportedModels.some((model) => model.id === chatCompletion.model);
}

function getMessages(chatCompletion, role) {
  if (role !== 'user' && role !== 'assistant') {
    throw new Error('Invalid role');
  }
  return chatCompletion.messages.filter((msg) => msg.role === role);
}

function countTotalCharacters(chat) {
  return chat.messages.reduce((total, msg) => total + msg.content.length, 0);
}

function trimChatMessages(chatCompletion, maxCharacters, trimDirection) {
  let total = countTotalCharacters(chatCompletion);
  const messages = chatCompletion.messages;

  if (total <= maxCharacters) return;

  while (total > maxCharacters && messages.length > 0) {
    const index = trimDirection === 'start' ? 0 : messages.length - 1;
    const removed = messages.splice(index, 1)[0];
    total -= removed.content.length;
  }

  if (messages.length === 0) {
    throw new Error(
      'Trimming all messages is necessary to meet the maxCharacters limit, which is not allowed.'
    );
  }
}

function formatChatCompletionToHTML(chatCompletion) {
  let html = `        <header>Model: ${chatCompletion.model}</header>`;
  for (const msg of chatCompletion.messages) {
    const roleCapitalized = msg.role.charAt(0).toUpperCase() + msg.role.slice(1);
    html += `\n        <section class="${msg.role}">${roleCapitalized}: ${msg.content}</section>`;
  }
  return `<article>\n${html}\n      </article>`;
}

function formatChatCompletionToHTML2(chatCompletion) {
  const sections = chatCompletion.messages.map((msg) => {
    const roleCapitalized = msg.role.charAt(0).toUpperCase() + msg.role.slice(1);
    return `        <section class="${msg.role}">${roleCapitalized}: ${msg.content}</section>`;
  });
  return `<article>\n        <header>Model: ${chatCompletion.model}</header>\n${sections.join('\n')}\n      </article>`;
}

function addUserName(chatData, defaultName) {
  chatData.messages.forEach((msg) => {
    if (msg.role === 'user' && !msg.name) {
      msg.name = defaultName;
    }
  });
}

function copySystemPrompts(source, target) {
  const newSystemPrompts = source.messages.filter((msg) => msg.role === 'system');
  const otherMessages = target.messages.filter((msg) => msg.role !== 'system');
  target.messages = [...newSystemPrompts, ...otherMessages];
  return target;
}

export {
  buildChatApiUrl,
  isValidApiKey,
  maskApiKey,
  isModelSupported,
  getMessages,
  countTotalCharacters,
  trimChatMessages,
  formatChatCompletionToHTML,
  formatChatCompletionToHTML2,
  addUserName,
  copySystemPrompts
};
