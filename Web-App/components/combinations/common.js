export function getElementsFromInput(input) {
  let elements = input.split(",");
  for (let i = 0; i < elements.length; ++i) {
    elements[i] = elements[i].trim();
  }

  return elements;
}
