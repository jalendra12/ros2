async function refreshAccessToken() {
  // Your logic to refresh token, e.g., call /refresh endpoint
  // Should throw if refresh fails
  try {
    const res = await axios.post('/auth/refresh-token');
    // Assume new token is in res.data.accessToken
    const newToken = res.data.accessToken;

    // Save token wherever you keep it, e.g. localStorage or axios defaults
    axios.defaults.headers.common['Authorization'] = 'Bearer ' + newToken;

    return true; // refresh succeeded
  } catch (error) {
    if (error.response && error.response.status === 401) {
      // Refresh token expired or invalid
      return false;
    }
    throw error; // some other error, throw up
  }
}

async function postWithTokenRetry(url, data, config = {}) {
  try {
    // First try
    const response = await axios.post(url, data, config);
    return response;
  } catch (error) {
    if (error.response && error.response.status === 401) {
      // Try refresh token
      const refreshed = await refreshAccessToken();

      if (!refreshed) {
        // Refresh failed with 401 → redirect to login
        window.location.href = '/login';
        return; // stop here
      }

      try {
        // Retry original request once
        const retryResponse = await axios.post(url, data, config);
        return retryResponse;
      } catch (retryError) {
        // Retry failed again — just ignore silently (or you can log)
        console.error("Retry failed:", retryError);
        return; 
      }
    }
    // Other errors, just throw
    throw error;
  }
}
