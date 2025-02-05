# Gemini API Test

This project demonstrates how to integrate the Gemini API for generating text content using Qt and QML. The application allows users to input a prompt and generate text based on that prompt using the Gemini API.

## Features

- **Text Input**: Users can enter a prompt in a text area.
- **Generate Content**: Clicking the "Generate content" button sends the prompt to the Gemini API and displays the generated text.
- **Error Handling**: Displays error messages if the API request fails.

## Requirements

- Qt 6.8 or later
- CMake 3.16 or later
- A valid API key for the Gemini API

## Setup

1. **Clone the Repository**:

   ```bash
   git clone https://github.com/deniskropp/GeminiAPITest.git
   cd GeminiAPITest
   ```
2. **Build the Project**:

   ```bash
   cmake -B build
   cmake --build build
   ```
3. **Run the Application**:

   ```bash
   ./build/appAPITest
   ```

## Usage

1. **Enter a Prompt**: Type your prompt in the text area.
2. **Generate Content**: Click the "Generate content" button.
3. **View Results**: The generated text will appear below the button.

## Notes

- **API Key**: Replace the placeholder API key in `main.cpp` with your actual Gemini API key.
- **Error Handling**: The application includes basic error handling to display any issues that occur during the API request.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Contributing

Contributions are welcome! Please feel free to submit pull requests or open issues for any improvements or bug fixes.

## Contact

For any questions or support, please contact [your-email@example.com](mailto:your-email@example.com).

---

**Note**: Ensure you have the necessary permissions and comply with the terms of service for the Gemini API when using this project.
