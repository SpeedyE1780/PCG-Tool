export async function PCGRequest(requestURL, requestBody, callback) {
  var request = {
    method: "POST",
    headers: {
      "content-type": "application/json",
    },
    body: JSON.stringify(requestBody),
  };

  const result = await fetch(requestURL, request);

  if (result.ok) {
    result
      .text()
      .then((body) => {
        callback(body);
      })
      .catch((err) => console.log(err));
  } else {
    console.log(result.status);
  }
}
